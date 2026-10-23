# Proposal: LLM-scheduled adequate test generation

**Status:** implemented in skill scripts + `02-run-adequate-suites.sh`.  
**Git marker:** tag `no-llm-support` is the pre-LLM experiment snapshot (history only).

## Motivation

Prior runs produced large false-EQUIVALENT rates because probes were weak, CSV kept non-killing rows, and Proteum kill marks were not refreshed after deletes. Attempt budget was an opaque integer that did not name the generator.

## Goals

1. Keep a test in CSV **and** Proteum **only** if:
   - original `./runner` succeeds, **and**
   - the case **kills the target mutant**.
2. Otherwise **rollback**: remove CSV row + `testset` line, `tcase -d -x <proteum_index>`, then **`exemuta -exec`** and re-`muta -l`.
3. Attempt budget = **`LLM_GEN_MODELS`** in `.env` (comma-separated model ids; length = attempts; duplicates allowed).
4. Each attempt uses **`API_KEYS` / `API_URLS`** (broadcast one value, or one per model).
5. Each LLM call gets **original + mutated** source and returns CSV fields + rationality; after exhaustion, **`LLM_EQUIV_MODEL`** writes equivalence rationality.

## Configuration (`.env`)

```bash
LLM_GEN_MODELS=composer-2,composer-2,gpt-5.6-sol-medium

# Length 1 ⇒ reuse for every model; or same length as LLM_GEN_MODELS
API_KEYS=sk-...
API_URLS=https://api.openai.com/v1

LLM_EQUIV_MODEL=composer-2
```

| Setting | Meaning |
|---------|---------|
| `LLM_GEN_MODELS` | Attempt schedule; `n` entries ⇒ `n` kill attempts |
| `API_KEYS` | Secrets; length `1` or `n` |
| `API_URLS` | Base URLs; length `1` or `n` |
| `LLM_EQUIV_MODEL` | Model for equivalence rationality after all kills fail |

**Broadcast rule:** `len(API_KEYS)==1` (resp. `API_URLS`) ⇒ use that value for all models. If `len > 1`, it must equal `len(LLM_GEN_MODELS)`. Missing/empty required key or URL ⇒ hard error. Missing `LLM_GEN_MODELS` ⇒ hard error (no silent fallback).

Do not log or persist raw API keys in status JSON.

## Per-mutant algorithm

```
for each alive mutant M:
  inspect(M) → Get on:, build-view, function, schema
  load original + mutated sources for owning function

  for i, model in enumerate(LLM_GEN_MODELS):
      key = API_KEYS[0] if len(API_KEYS)==1 else API_KEYS[i]
      url = API_URLS[0] if len(API_URLS)==1 else API_URLS[i]
      prompt(model, url, key, original, mutant, schema, prior_failures)
      → fields, rationality
      append CSV + testset line (temporary)
      validate original runner
      if fail:
          remove CSV/testset row; continue   # never tcase-add
      tcase -add → proteum_index
      exemuta -exec -f M -t M
      muta -l M
      if Dead:
          KEEP csv + proteum TC; finalize KILLED; break
      else:
          ROLLBACK:
            remove CSV row + testset line
            tcase -d -x proteum_index SESSION
            exemuta -exec -f M -t M
            muta -l M
          record attempt (failed kill); continue

  if still Alive:
      ask LLM_EQUIV_MODEL for equivalence_rationality
      finalize EQUIVALENT (muta -equiv) only with elaborated rationality
```

### Rollback atomicity

**CSV remove + `tcase -d -x` + `exemuta -exec` + `muta -l`** as one unit. Prefer deleting the last-added TC to avoid index surprises.

### What stays in the suite

Only tests that killed their **target**. Non-killers must not remain.

## LLM prompt contract (kill attempt)

**Inputs:** program, operator, mutant id; function + CSV headers + format example; `Get on:` + build-view; original and mutated function source; prior failed field sets.

**Output (JSON):**

```json
{
  "function": "digit_reverser",
  "fields": { "N": "123", "expected_output": "", "expected_stdout": "" },
  "rationality": "why this input reaches Get on: and distinguishes mutant"
}
```

Oracles: `CUNIT_CAPTURE` on the original after inputs are chosen (LLM may leave oracle columns empty).

## Equivalence contract

Exhausting `LLM_GEN_MODELS` is evidence, not the explanation. Require semantic rationality (SKILL.md). Use `LLM_EQUIV_MODEL`.

## Implementation plan

| Phase | Work |
|-------|------|
| P0 | `.env` loader: `LLM_GEN_MODELS`, `API_KEYS`, `API_URLS`, `LLM_EQUIV_MODEL` |
| P1 | `rollback_attempt.py` (CSV + testset + `tcase -d -x` + `exemuta -exec`) |
| P2 | Keep-only-on-kill in attempt/finalize path |
| P3 | LLM client + `propose_kill_case.py` (original vs mutant in prompt) |
| P4 | Equivalence LLM pass; forbid budget-only rationality |
| P5 | Wire `02-run-adequate-suites.sh`; pilot re-run |

## Pilot programs

| Priority | Program | Prior EQ% | Finalized | Why |
|----------|---------|-----------|-----------|-----|
| 1 | **CheckPalindrome** | 81.9% | 166 | Smallest high-EQ smoke |
| 2 | **DigitReverser** | 100% | 496 | Worst EQ rate |
| 3 | **twoPred** | 74.0% | 246 | Simple predicates |
| 4 | **RecursiveSelectionSort** | 90.8% | 555 | High EQ, bounded |
| 5 | **Stack** | 70.3% | 451 | ADT pressure |

File: `scripts/pilot-llm-high-equiv.txt`.

## Success metrics

- Lower EQ rate on pilots vs prior summaries  
- `ts_<OP>/` rows ≈ killing tests only  
- After rollback, target is Alive before next attempt  
- Status JSON: per-attempt `llm_name` (= model id); no raw keys stored  
