# Experiment scripts

Shared CLI flags:

| Flag | Meaning |
|------|---------|
| `--programs-dir <path>` | Root directory containing one subdirectory per program |
| `--programs-file <path>` | Text file with program directory names (one per line; `#` comments allowed in consumers that support it) |
| `--operators-list <path>` | Optional mutation-operator list (default: `scripts/unit-operators-list.txt`) |

`--programs-file` is used as given (relative to the current working directory or absolute). It is **not** automatically prefixed with `--programs-dir`.

---

## `00-create-test-session.sh`

Creates a Proteum/IM test session per program: compile original and instrumented code, generate unit mutants, write the initial report, and inventory mutant IDs per operator.

Uses `test-new -E runner` so the session executable name matches `compile_cunit.txt` (`-o runner`). If those diverge, Proteum marks mutants **Anomalous** and they cannot be executed/killed.

```bash
scripts/00-create-test-session.sh \
  --programs-dir <path> \
  --programs-file <path> \
  [--operators-list <path>]
```

**Example**

```bash
scripts/00-create-test-session.sh \
  --programs-dir programs-v1 \
  --programs-file programs.txt
```

**Main outputs** (under each `<programs-dir>/<PROG>/`)

- `runner`, `runner_instr`
- Proteum session `S_<PROG>.*`
- `report-initial.lst`
- `mutants/<OP_ACRONYM>.txt` — mutant IDs for that operator (one ID per line; empty if none)
- `mutants/total-mutants-per-operator.csv` — `OP_CODE,OP_ACRONYM,TOTAL`
- `mutants.txt` — full `muta -l` listing

---

## `01-ordering-alive-mutants.sh`

Reorders mutant IDs in each `mutants/<OP_ACRONYM>.txt` **in place** (after step `00`). Guarantees no mutant ID is lost: length and set equality are checked before an atomic overwrite.

```bash
scripts/01-ordering-alive-mutants.sh \
  --programs-dir <path> \
  --programs-file <path> \
  --order <random|ascending|descending> \
  [--seed <int>] \
  [--operators-list <path>]
```

| Flag | Required | Description |
|------|----------|-------------|
| `--programs-dir` | yes | Programs root |
| `--programs-file` | yes | Program names list |
| `--order` | yes | `random`, `ascending`, or `descending` (numeric by mutant ID) |
| `--seed` | only if `--order random` | Integer seed for a deterministic shuffle; ignored for other modes |
| `--operators-list` | no | Override default `unit-operators-list.txt` |

This script calls the Python worker `ordering-alive-mutants.py`. For `--order random`, IDs are sorted ascending before shuffling so the same `--seed` always yields the same order regardless of the previous on-disk order.

**Examples**

```bash
scripts/01-ordering-alive-mutants.sh \
  --programs-dir programs-v1 \
  --programs-file programs.txt \
  --order ascending

scripts/01-ordering-alive-mutants.sh \
  --programs-dir programs-v1 \
  --programs-file programs.txt \
  --order random \
  --seed 42
```

---

## `ordering-alive-mutants.py`

Python 3 worker used by `01-ordering-alive-mutants.sh`. Prefer the shell driver for the public CLI; invoke the worker directly only for debugging.

```bash
scripts/ordering-alive-mutants.py \
  --programs-dir <path> \
  --programs-file <path> \
  --operators-list <path> \
  --order <random|ascending|descending> \
  [--seed <int>]
```

---

## Operator list files

| File | Contents |
|------|----------|
| `unit-operators-list.txt` | Unit operators (`u-*`), rows `OP_CODE,OP_ACRONYM` |
| `integration-operators-list.txt` | Integration operators (`I-*` / `II-*`), same format |

Codes and acronyms match Proteum/IM `g_tab_operador[]` in `globais.c`.

---

## `02-run-adequate-suites.sh`

Batch driver: for each program, runs the skill helpers for every unit operator
with alive mutants.

**Baseline (current code, tag `no-llm-support`):** heuristic
`--mutation-oriented-input-generation` and `MAX_ITERATIONS` (default 5).

**Target (see skill `PROPOSAL-llm-gen-models.md`):** read repo `.env`
`LLM_GEN_MODELS` (attempt schedule / models), keep CSV+Proteum tests only when
they kill the target, otherwise `tcase -d -x` + **`exemuta -exec`**.

```bash
# Baseline heuristic run
MAX_ITERATIONS=5 \
scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt

# After LLM path is implemented: configure models then run the same driver
cp .env.example .env   # set LLM_GEN_MODELS=...
scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt
```

Requires sessions from `00` first. Per operator it clears Proteum test cases,
seeds `ts_<OP>/`, and writes `mutants/<OP>_execution_status.json`.
Progress logs: `<prog>/mutants/adequate-run-logs/`.

**Pilot list (high EQ rate, moderate size):** `scripts/pilot-llm-high-equiv.txt`
(CheckPalindrome, DigitReverser, twoPred, RecursiveSelectionSort, Stack).

`02-run-adequate-suites-boundedQueue.sh` is a thin wrapper for boundedQueue only.

Aggregate after (also refreshed during the run):

```bash
python3 .cursor/skills/mutation-operator-adequate-test-set/scripts/summarize_status.py \
  --program-dir programs-v1/CheckPalindrome
```

Outputs: `mutants/adequate-suite-summary.json` and `.csv`.

When a mutant is marked possible-equivalent, the helpers also run
`muta -equiv -x <id> S_<PROG>` and append the ID to `equivalents_<OP>.txt`.

Verify that the union of those files matches status-JSON `EQUIVALENT` entries:

```bash
python3 .cursor/skills/mutation-operator-adequate-test-set/scripts/verify_equivalents.py \
  --program-dir programs-v1/boundedQueue \
  --write-merged programs-v1/boundedQueue/equivalents_ALL.txt
```

**Do not reuse `ts_data` rows as killing tests** in new runs. That directory is
only a CSV format reference; invent mutation-specific cases
(`inspect_mutant.py` → LLM or heuristic → `run_attempt.py`).

---

## Research-question analysis (`scripts/analysis/`)

Builds a LaTeX report for RQ1–RQ4 (operator + category; per program and pooled):

```bash
scripts/analysis/run_rq_analysis.sh programs-v1 programs-v1/_analysis
pdflatex -output-directory programs-v1/_analysis programs-v1/_analysis/rq_report.tex
```

Outputs: `mutant_records.csv`, `rq_results.json`, `rq_report.tex` (+ PDF if latex succeeds).

---

## Skill: mutation-operator-adequate-test-set

After `00` and `01`, build one adequate CUnit suite **per operator** using:

`.cursor/skills/mutation-operator-adequate-test-set/`

Design proposal (LLM schedule, keep-only-if-kills, Proteum rollback+re-exec):

`PROPOSAL-llm-gen-models.md` in that skill directory.

Ask the agent to apply the skill, e.g.:

```text
Apply mutation-operator-adequate-test-set on programs-v1 with
scripts/pilot-llm-high-equiv.txt. Use .env LLM_GEN_MODELS. Keep tests only
when original OK and target killed; on failure tcase -d -x then exemuta -exec.
```

| Config | Role |
|--------|------|
| `.env` → `LLM_GEN_MODELS` | **Target:** models for successive kill attempts (length = budget) |
| `.env` → `API_KEYS` / `API_URLS` | **Target:** length 1 (shared) or match `LLM_GEN_MODELS` |
| `.env` → `LLM_EQUIV_MODEL` | **Target:** equivalence rationality after failures |
| `--max-iterations` | **Legacy:** heuristic-only budget (tag `no-llm-support`) |

Per-operator outputs under each program:

| Path | Role |
|------|------|
| `ts_<OP>/test_cases_*.csv` | Operator suite (target: **only killing** rows) |
| `testset_<OP>.txt` | `<function> <test_number>` lines |
| `mutants/<OP>.txt` | Remaining alive IDs |
| `mutants/<OP>_execution_status.json` | Per-mutant / **per-attempt** metrics |

Helpers: `.cursor/skills/mutation-operator-adequate-test-set/scripts/`.  
Schema: `SKILL.md`, `reference.md`.

**Metrics note:** unknown token/cost → `null` + `"source": "unavailable"` — never `0`.

**Git baseline:** `git tag no-llm-support` marks the last heuristic-only complete run.

---

## Legacy / draft

`01-running-test-cases.sh` is an older draft that mixes session creation with test-case import and mutant execution. It is **not** part of the current step-1 pipeline (`00` → `01-ordering-alive-mutants`). Future steps may renumber or replace it.
