---
name: mutation-operator-adequate-test-set
description: >-
  Builds one adequate CUnit test set per Proteum/IM mutation operator for
  programs under programs-*/ with runner/runner_instr sessions. Records
  precise per-attempt timing and token/cost metrics in
  mutants/<OP>_execution_status.json. Use when creating operator-adequate
  suites, killing alive mutants, running the mutation experiment skill,
  LLM_GEN_MODELS, or operator execution status JSON.
disable-model-invocation: true
---

# Mutation-operator adequate test set

Build an adequate test suite **per mutation operator**: generate CUnit CSV cases
until every mutant in `mutants/<OP>.txt` is KILLED or marked **possible
EQUIVALENT** after the configured attempt schedule is exhausted.

**Baseline (shipped code today):** tag `no-llm-support` — heuristic
`--mutation-oriented-input-generation`, integer `--max-iterations` (default 5),
CSV rows kept even when they do not kill.

**Target design (implement next):** see
[PROPOSAL-llm-gen-models.md](PROPOSAL-llm-gen-models.md). Summary below is the
**intended** contract; follow it when implementing or when the user asks to run
the LLM path.

Helpers live in this skill’s `scripts/`. Always use them for status JSON and
alive-list updates so metrics stay consistent.

## Parameters

| Param | Notes |
|-------|-------|
| `--programs-dir` | Required (e.g. `programs-v1`) |
| `--programs-file` | Required (program names, one per line) |
| `--operators-list` | Default `scripts/unit-operators-list.txt` |
| `LLM_GEN_MODELS` | **Target:** from repo `.env` — comma-separated model ids; **length = attempt budget**; each entry used once per mutant |
| `API_KEYS` | **Target:** comma-separated secrets; length `1` (reuse for all models) or same length as `LLM_GEN_MODELS` |
| `API_URLS` | **Target:** comma-separated base URLs; length `1` or match `LLM_GEN_MODELS` (same broadcast rule) |
| `LLM_EQUIV_MODEL` | **Target:** optional model for equivalence rationality after all kill attempts fail |
| `HEURISTIC_FIRST` | **Target:** `0`/`1` — optional one heuristic probe before the model list |
| `--max-iterations` | **Legacy (baseline only):** integer budget when using heuristic-only mode |
| `--llm-name` | Recorded in status JSON; under LLM schedule, prefer **per-attempt** model id from the list |

### `.env` (target)

```bash
# Attempt schedule: N models ⇒ N kill attempts (duplicates allowed)
LLM_GEN_MODELS=composer-2,composer-2,gpt-5.6-sol-medium

# One key/URL for all models, or one per LLM_GEN_MODELS entry
API_KEYS=sk-...
API_URLS=https://api.openai.com/v1

# After all kill attempts fail, ask this model for equivalence rationality
LLM_EQUIV_MODEL=composer-2

# Optional: 1 = one heuristic probe before LLM_GEN_MODELS
HEURISTIC_FIRST=0
```

Copy from [`.env.example`](../../../.env.example) at the repo root. Do not commit
secrets; `.env` is gitignored. Never log full `API_KEYS` values.

## Prerequisites (each program directory)

- `PROTEUMIMHOME` on `PATH` (`exemuta`, `muta`, `tcase`, …)
- Session from `scripts/00-create-test-session.sh`: `S_<PROG>.*`, `runner`, `runner_instr`
- Ordered alive lists from `scripts/01-ordering-alive-mutants.sh`: `mutants/<OP>.txt`
- Baseline CSV schemas in `ts_data/test_cases_*.csv` and `functions.txt`

Prefer an empty Proteum test-case set for a clean operator suite (`tcase -l`
shows none).

**Session executable name:** `test-new -E runner` must match `compile_cunit.txt`
(`-o runner`). Mismatch ⇒ **Anomalous** mutants that cannot be killed.

## Artifacts

| Path | Role |
|------|------|
| `ts_<OP>/test_cases_<fn>.csv` | Operator suite (same schema as `ts_data`) |
| `testset_<OP>.txt` | Lines: `<function> <test_number>` |
| `mutants/<OP>.txt` | Remaining alive IDs only |
| `mutants/<OP>_execution_status.json` | **Authoritative metrics** |
| `equivalents_<OP>.txt` | Possible-equivalent IDs; also `muta -equiv` |

**Target keep rule:** a CSV row / Proteum TC remains **only** if original runner
OK **and** the case killed the **target** mutant. Otherwise rollback (below).

## Metrics rules (critical)

1. Record **one attempt object per try**, even if validation fails before `tcase -add`.
2. Timestamps: ISO-8601 with nanoseconds (`date --rfc-3339=ns | tr ' ' T`).
3. `duration_ms` from helpers — do not invent it.
4. Tokens/cost unknown ⇒ **`null`** + `"source": "unavailable"` — never `0`.
5. Update status JSON **before** removing IDs from `mutants/<OP>.txt`.
6. Collateral kills: finalize with `killed_by_mutant_target` = current target.

Full schema: [reference.md](reference.md).

## Target algorithm (LLM schedule + keep-only-if-kills)

For each operator `OP`, each program `P`, each alive mutant `M`:

1. `inspect_mutant.py` + load **original** and **mutated** sources for the owning function.
2. For each `model` in `LLM_GEN_MODELS` (after optional heuristic):
   1. Ask `model` for CSV `fields` + kill `rationality` (original vs mutant code in prompt).
   2. Temporarily append CSV + `testset` line; fill oracles via `CUNIT_CAPTURE` if needed.
   3. Validate `./runner --data ts_<OP> <fn> <n>` — if fail: remove CSV/testset row; record attempt; continue (no `tcase -add`).
   4. `tcase -add` → note `proteum_tcase_index`.
   5. `exemuta -exec -f M -t M` then `muta -l`.
   6. If **Dead**: **keep** CSV + Proteum TC; finalize KILLED; stop attempts for `M`.
   7. If **Alive**: **rollback** then continue:
      - Remove CSV row + `testset` line  
      - `tcase -d -x <proteum_tcase_index> S_<P>`  
      - **`exemuta -exec -f M -t M`** (mandatory — refresh kill marks after delete)  
      - `muta -l` (expect Alive)  
      - `record-attempt` with failed kill
3. If still Alive after the list: ask `LLM_EQUIV_MODEL` (or last model) for
   **equivalence rationality** → finalize EQUIVALENT (`muta -equiv`).

### Rollback (mandatory when not keeping)

```text
CSV/testset remove  →  tcase -d -x <idx> SESSION  →  exemuta -exec  →  muta -l
```

Never leave a non-killing TC in Proteum without re-exec; status would be stale.

## Baseline algorithm (tag `no-llm-support` — current code)

`run_operator.py --mutation-oriented-input-generation --max-iterations N`:

- Heuristic inputs from `Get on:` + schema; oracles via `CUNIT_CAPTURE`.
- Up to `N` attempts; **no LLM API**.
- CSV rows are **not** removed on non-kill (legacy behaviour).
- Exhaustion ⇒ EQUIVALENT with template rationality.

Use only for comparison against `no-llm-support` or until the LLM path ships.

## Helper commands

`SKILL_SCRIPTS` = this skill’s `scripts/` directory.

```bash
python3 "$SKILL_SCRIPTS/seed_operator_ts.py" --program-dir . --operator <OP>
python3 "$SKILL_SCRIPTS/update_execution_status.py" init \
  --program-dir . --operator <OP> --session S_<PROG> \
  --max-iterations <N> --llm-name "<name>"
python3 "$SKILL_SCRIPTS/inspect_mutant.py" \
  --program-dir . --session S_<PROG> --mutant-id <ID>
python3 "$SKILL_SCRIPTS/run_attempt.py" \
  --program-dir . --operator <OP> --session S_<PROG> \
  --mutant-id <ID> --iteration <i> --function <fn> \
  --fields-json '{...}' --rationality "..." --llm-name "<name>"
# Target (to implement): rollback_attempt.py after non-kill
```

## Generating tests (critical)

**Do not reuse `ts_data/` rows as killing tests** — schema reference only.

**Target:** LLM invents inputs from original + mutant sources + `Get on:`.  
**Baseline:** `mutation_oriented_input_generation.py` (no LLM).

Oracles from **original** `./runner` (`CUNIT_CAPTURE`). Attempt rationality must
target **this** mutation.

## Equivalence rationality (critical)

Exhausting `LLM_GEN_MODELS` (or legacy `max_iterations`) is **evidence**, not
the explanation. Require semantic rationality (what changed, why observationally
identical, what was tried, residual doubt). Forbidden: “Alive after N attempts.”

## How to run / test

### Baseline (current implementation)

```bash
git checkout no-llm-support   # optional: exact heuristic baseline

scripts/00-create-test-session.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt

scripts/01-ordering-alive-mutants.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt \
  --order ascending

# Heuristic adequate suites (legacy)
MAX_ITERATIONS=5 \
scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt
```

### Target LLM path (after implementation)

```bash
cp .env.example .env   # edit LLM_GEN_MODELS

# Ask Cursor to apply this skill on the pilot list, or:
scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt
# (driver will read .env and use LLM schedule instead of heuristic-only)
```

### Single operator smoke (debug)

```bash
scripts/diag-run-one-operator.sh \
  --programs-dir programs-v1 \
  --program CheckPalindrome \
  --operator u-CRCR
```

### Cursor skill invocation

Ask the agent (with this skill):

```text
Apply mutation-operator-adequate-test-set on programs-v1 using
scripts/pilot-llm-high-equiv.txt. Load .env LLM_GEN_MODELS. Keep CSV/Proteum
tests only when original OK and target killed; otherwise tcase -d -x + exemuta -exec.
```

### Compare vs baseline

```bash
python3 .cursor/skills/mutation-operator-adequate-test-set/scripts/summarize_status.py \
  --program-dir programs-v1/CheckPalindrome
# Compare adequate-suite-summary.json eq rate to tag no-llm-support results
```

## Pilot checklist

```
- [ ] Tag no-llm-support available for rollback comparison
- [ ] .env with LLM_GEN_MODELS set (LLM path)
- [ ] PROTEUMIMHOME set; runner rebuilt
- [ ] Pilot file scripts/pilot-llm-high-equiv.txt
- [ ] Empty or intentional tcase set per operator start
- [ ] After non-kill: CSV removed + tcase -d -x + exemuta -exec verified
- [ ] Review mutants/<OP>_execution_status.json (per-attempt llm_name)
```
