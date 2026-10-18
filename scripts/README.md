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
with alive mutants (automated candidate proposer + `run_attempt.py`).

```bash
# optional: MAX_ITERATIONS=5 LLM_NAME=composer-automated-proposer
scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-cal-UnixCal.txt
```

Requires sessions from `00` first. Per operator it clears Proteum test cases,
seeds `ts_<OP>/`, and writes `mutants/<OP>_execution_status.json`.
Progress logs: `<prog>/mutants/adequate-run-logs/`.

`02-run-adequate-suites-boundedQueue.sh` is a thin wrapper for boundedQueue only.

Aggregate after (also refreshed during the run):

```bash
python3 .cursor/skills/mutation-operator-adequate-test-set/scripts/summarize_status.py \
  --program-dir programs-v1/cal
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

Backfill an already-finished program:

```bash
python3 .cursor/skills/mutation-operator-adequate-test-set/scripts/backfill_equivalents.py \
  --program-dir programs-v1/boundedQueue
```

**Do not reuse `ts_data` rows as killing tests** in new runs. That directory is
only a CSV format reference; the skill must invent mutation-specific cases
(`inspect_mutant.py` → LLM → `run_attempt.py`).

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

After `00` and `01`, build one adequate CUnit suite **per operator** using the project skill:

`.cursor/skills/mutation-operator-adequate-test-set/`

Ask the agent to apply that skill with the same style of flags:

```text
--programs-dir <path>
--programs-file <path>
--operators-list <path>     # optional; default scripts/unit-operators-list.txt
--max-iterations <int>      # optional; default 5
--llm-name <str>            # recorded into status JSON
```

**Changing `max_iterations`:** pass `--max-iterations N`, or say e.g. “use max_iterations=10”.
If omitted, the skill uses **5**. The effective value is stored in
`mutants/<OP>_execution_status.json` as `max_iterations`.

Per-operator outputs under each program:

| Path | Role |
|------|------|
| `ts_<OP>/test_cases_*.csv` | Operator suite (same schema as `ts_data`) |
| `testset_<OP>.txt` | `<function> <test_number>` lines |
| `mutants/<OP>.txt` | Remaining alive IDs |
| `mutants/<OP>_execution_status.json` | Per-mutant / **per-attempt** metrics |

Helpers used by the skill live under
`.cursor/skills/mutation-operator-adequate-test-set/scripts/`. Details and JSON
schema: that skill’s `SKILL.md` and `reference.md`.

**Metrics note:** unknown token/cost values are stored as `null` with
`"source": "unavailable"` — never as `0`.

---

## Legacy / draft

`01-running-test-cases.sh` is an older draft that mixes session creation with test-case import and mutant execution. It is **not** part of the current step-1 pipeline (`00` → `01-ordering-alive-mutants`). Future steps may renumber or replace it.
