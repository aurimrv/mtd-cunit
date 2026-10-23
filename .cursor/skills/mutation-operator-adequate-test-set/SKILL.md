---
name: mutation-operator-adequate-test-set
description: >-
  Builds one adequate CUnit test set per Proteum/IM mutation operator for
  programs under programs-*/ with runner/runner_instr sessions. Uses
  LLM_GEN_MODELS from .env for kill attempts; records metrics in
  mutants/<OP>_execution_status.json. Use when creating operator-adequate
  suites, killing alive mutants, or configuring API_KEYS / API_URLS.
disable-model-invocation: true
---

# Mutation-operator adequate test set

Build an adequate test suite **per mutation operator**: for each alive mutant,
ask models listed in `LLM_GEN_MODELS` to invent CUnit CSV cases (original +
mutated source in the prompt) until the mutant is KILLED or the schedule is
exhausted and the mutant is marked **possible EQUIVALENT**.

Design details: [PROPOSAL-llm-gen-models.md](PROPOSAL-llm-gen-models.md).

Helpers live in this skill’s `scripts/`. Always use them for status JSON and
alive-list updates so metrics stay consistent.

## Configuration (`.env`)

```bash
LLM_GEN_MODELS=gpt-4o-mini,gpt-4o-mini
API_KEYS=sk-...
API_URLS=https://api.openai.com/v1
LLM_EQUIV_MODEL=gpt-4o-mini
```

| Variable | Role |
|----------|------|
| `LLM_GEN_MODELS` | Comma-separated model ids; **length = attempt budget** |
| `API_KEYS` | Length `1` (shared) or match `LLM_GEN_MODELS` |
| `API_URLS` | OpenAI-compatible base URL(s); same length rule |
| `LLM_EQUIV_MODEL` | Model for equivalence rationality after failures |
| `DOTENV_PATH` | Optional absolute path to `.env` |

Copy from repo `.env.example`. Never commit `.env` or log raw keys.

## Prerequisites

- `PROTEUMIMHOME` on `PATH`
- Session from `scripts/00-create-test-session.sh`
- Ordered alive lists from `scripts/01-ordering-alive-mutants.sh`
- `ts_data/` CSV schemas + `functions.txt`
- Repo `.env` configured

`test-new -E runner` must match `compile_cunit.txt` (`-o runner`).

## Keep / rollback rules

A case stays in `ts_<OP>/` and Proteum **only** if original `./runner` OK **and**
the **target** mutant is Dead. Otherwise:

1. Remove CSV row + `testset_<OP>.txt` line  
2. `tcase -d -x <proteum_index> S_<PROG>`  
3. **`exemuta -exec -f ID -t ID`** (refresh kill marks)  
4. `muta -l` (expect Alive)

## Algorithm (per mutant)

1. `inspect_mutant.py` + original/mutated sources  
2. For each `(model, key, url)` from `.env`:  
   `propose_kill_case` → `run_attempt` → keep if kill, else `rollback_attempt`  
3. If still Alive: `LLM_EQUIV_MODEL` writes rationality → mark EQUIVALENT  

## How to run

```bash
cp .env.example .env   # edit models + keys + URLs

scripts/00-create-test-session.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt

scripts/01-ordering-alive-mutants.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt \
  --order ascending

scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt
```

Single operator:

```bash
scripts/diag-run-one-operator.sh \
  --program CheckPalindrome --operator u-CRCR --limit 2 --timeout 300
```

### Cursor skill

```text
Apply mutation-operator-adequate-test-set on programs-v1 using
scripts/pilot-llm-high-equiv.txt. Load .env. Keep tests only when original OK
and target killed; otherwise tcase -d -x + exemuta -exec.
```

## Equivalence rationality

Exhausting `LLM_GEN_MODELS` is evidence, not the explanation. Require semantic
reasoning (Get on:, why observationally identical, what was tried, residual
doubt). Forbidden: “Alive after N attempts” alone.

## Artifacts

| Path | Role |
|------|------|
| `ts_<OP>/test_cases_*.csv` | **Killing** cases only |
| `testset_<OP>.txt` | `<function> <n>` |
| `mutants/<OP>.txt` | Remaining alive IDs |
| `mutants/<OP>_execution_status.json` | Metrics (`llm_gen_models`, per-attempt `llm_name`) |
| `equivalents_<OP>.txt` | Possible equivalents |

## Pilot programs

`scripts/pilot-llm-high-equiv.txt`: CheckPalindrome, DigitReverser, twoPred,
RecursiveSelectionSort, Stack.
