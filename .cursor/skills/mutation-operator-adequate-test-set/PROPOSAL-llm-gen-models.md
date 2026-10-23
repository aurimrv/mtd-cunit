# Proposal: LLM-scheduled adequate test generation

**Baseline tag:** `no-llm-support` (heuristic-only kill loop).  
**Status:** design approved; implementation pending.

## Problems with the baseline (`no-llm-support`)

1. **False EQUIVALENT mass** — after ≤5 heuristic probes, mutants are marked EQUIVALENT; ~97.6% of mutants that survive one valid non-kill never get killed by later heuristic attempts.
2. **CSV pollution** — every attempt row stays in `ts_<OP>/` even when it does not kill (and even when original validation fails).
3. **Proteum drift** — non-killing cases can remain in the session and skew later Alive/Dead unless deleted and re-executed.
4. **`max_iterations` is opaque** — an integer does not say *which* generator ran each attempt.

## Goals

1. Keep a test in CSV **and** Proteum **only** if:
   - original `./runner` succeeds, **and**
   - the case **kills the target mutant**.
2. Otherwise **rollback**: remove CSV row + `testset` line, `tcase -d -x <proteum_index>`, then **`exemuta -exec`** and re-`muta -l` so kill info is current.
3. Replace `max_iterations` with **`LLM_GEN_MODELS`** in `.env`: comma-separated model ids; **list length = attempt budget**; each entry is used once per mutant (duplicates allowed).
4. Each LLM attempt receives **original + mutated** source (and inspection context) and must return CSV fields + rationality; last failure may supply **equivalence rationality**.

## Configuration (`.env`)

```bash
# Required for LLM path: one attempt per entry (order = attempt order)
LLM_GEN_MODELS=composer-2,composer-2,gpt-5.6-sol-medium

# Provider credentials / base URLs (comma-separated).
# - One value each ⇒ reuse for every entry in LLM_GEN_MODELS
# - Same length as LLM_GEN_MODELS ⇒ per-attempt (API_KEYS[i], API_URLS[i], model[i])
API_KEYS=sk-...
API_URLS=https://api.openai.com/v1

# Optional: model used only to write equivalence rationality after all kills fail
LLM_EQUIV_MODEL=composer-2

# Optional: run one heuristic probe before the model list (default 0)
HEURISTIC_FIRST=0

# Optional: path override (default: repo-root .env)
# DOTENV_PATH=/path/to/.env
```

Semantics:

| Setting | Meaning |
|---------|---------|
| `LLM_GEN_MODELS` | Attempt schedule; `n` entries ⇒ `n` LLM kill attempts |
| `API_KEYS` | Secrets list; length `1` or `n` (must match models if `n > 1`) |
| `API_URLS` | Base URL list; length `1` or `n` (same rule as keys) |
| Same model thrice | Three independent calls (same or different key/url by index) |
| `heuristic` token (optional) | Allow embedding a non-LLM attempt in the list |
| Empty / missing list | Fail fast in LLM mode (do not silently fall back to 5 heuristic-only EQ) |

**Broadcast rule:** if `len(API_KEYS)==1` (resp. `API_URLS`), that single value is used for all models. If `len > 1`, it must equal `len(LLM_GEN_MODELS)` or the loader errors. Empty key/url for a required LLM attempt is a hard error.

Deprecate relying on `MAX_ITERATIONS` / `--max-iterations` for the LLM path; keep the flag only as a **legacy override** if `LLM_GEN_MODELS` is unset and `HEURISTIC_ONLY=1`.

## Per-mutant algorithm

```
for each alive mutant M:
  inspect(M) → Get on:, build-view, function, schema
  load original.c fragment + muta<M>_S_<P>.c (or build-view twin)

  for i, model in enumerate(LLM_GEN_MODELS):   # or [heuristic]+models
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
            exemuta -exec -f M -t M          # refresh kill marks
            muta -l M                        # expect Alive
          record attempt (failed kill) in status JSON
          continue

  if still Alive:
      ask LLM_EQUIV_MODEL (or last model) for equivalence_rationality
      finalize EQUIVALENT (muta -equiv) only with elaborated rationality
```

### Rollback atomicity

Treat as one unit: **CSV remove + `tcase -d -x` + `exemuta -exec` + `muta -l`**.  
Prefer deleting the **last-added** TC so Proteum index shifting stays simple.

### What stays in the suite

Only tests that killed their **target**. Collateral kills from retained tests may still occur when later mutants run against the growing session; that is acceptable. Non-killers must not remain.

## LLM prompt contract (kill attempt)

Inputs:

- Program name, operator, mutant id  
- Owning function + CSV headers + one format example  
- `Get on:` + truncated build-view  
- **Original** function source and **mutated** function source  
- Prior failed field sets (so retries are not blind)

Outputs (JSON):

```json
{
  "function": "digit_reverser",
  "fields": { "N": "123", "expected_output": "", "expected_stdout": "" },
  "rationality": "why this input reaches Get on: and distinguishes mutant"
}
```

Oracles: prefer `CUNIT_CAPTURE` on the original after inputs are fixed (LLM may leave oracle columns empty for capture fill).

## Equivalence contract

Surviving the model list is **not** sufficient wording. Require semantic rationality (see SKILL.md). Prefer a dedicated `LLM_EQUIV_MODEL` call.

## Implementation plan (phased)

| Phase | Work |
|-------|------|
| P0 | `.env` loader; parse `LLM_GEN_MODELS`, `API_KEYS`, `API_URLS` (broadcast or per-index); wire into `run_operator.py` / `02-run-adequate-suites.sh` |
| P1 | Rollback helper: `rollback_attempt.py` (CSV + testset + `tcase -d -x` + `exemuta -exec` + status check) |
| P2 | Keep-only-on-kill in `run_attempt.py` / finalize path |
| P3 | LLM client adapter (Cursor/model slug → completion); `propose_kill_case.py` |
| P4 | Equivalence LLM pass; forbid budget-only rationality |
| P5 | Docs + pilot scripts; reopen high-EQ programs for re-run |
| P6 | Optional `HEURISTIC_FIRST` / `heuristic` list token |

## Pilot programs (recommended)

High EQUIVALENT **rate**, moderate mutant count (good for LLM cost):

| Priority | Program | EQ% (baseline) | Finalized | Why |
|----------|---------|----------------|-----------|-----|
| 1 | **CheckPalindrome** | 81.9% | 166 | Smallest high-EQ; fast smoke |
| 2 | **DigitReverser** | 100% | 496 | Worst EQ rate; stdout harness; known false EQ |
| 3 | **twoPred** | 74.0% | 246 | Small/medium; simple predicates |
| 4 | **RecursiveSelectionSort** | 90.8% | 555 | High EQ, still bounded |
| 5 | **Stack** | 70.3% | 451 | ADT / multi-step pressure |

Avoid for first pilots: `replace`, `print_tokens*`, `pcal`, `UnixCal`, `stats` (large and/or fragile).

File: `scripts/pilot-llm-high-equiv.txt`.

## Success metrics

- Drop in EQ rate on pilots vs tag `no-llm-support` summaries  
- `ts_<OP>/` row count ≈ number of killing tests (not attempts × mutants)  
- After rollback, target mutant listed **Alive** before next attempt  
- Status JSON records `llm_name` **per attempt** (= list entry used)

## Non-goals (v1)

- Full multi-function scenario synthesis beyond CSV schema  
- Automatic harness rewriting  
- Pushing tags/remotes (operator decides)
