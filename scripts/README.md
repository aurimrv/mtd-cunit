# Experiment scripts

Shared CLI flags:

| Flag | Meaning |
|------|---------|
| `--programs-dir <path>` | Root directory containing one subdirectory per program |
| `--programs-file <path>` | Text file with program directory names (one per line; `#` comments allowed) |
| `--operators-list <path>` | Optional mutation-operator list (default: `scripts/unit-operators-list.txt`) |

`--programs-file` is used as given (relative to CWD or absolute). It is **not**
automatically prefixed with `--programs-dir`.

---

## `00-create-test-session.sh`

Creates a Proteum/IM test session per program: compile original and instrumented
code, generate unit mutants, write the initial report, and inventory mutant IDs
per operator.

```bash
scripts/00-create-test-session.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt
```

Uses `test-new -E runner` matching `compile_cunit.txt` (`-o runner`).

---

## `01-ordering-alive-mutants.sh`

Reorders mutant IDs in each `mutants/<OP>.txt` in place.

```bash
scripts/01-ordering-alive-mutants.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt \
  --order ascending
```

---

## Operator list files

| File | Contents |
|------|----------|
| `unit-operators-list.txt` | Unit operators (`u-*`), rows `OP_CODE,OP_ACRONYM` |
| `integration-operators-list.txt` | Integration operators |

---

## `02-run-adequate-suites.sh`

Batch driver: for each program/operator with alive mutants, runs
`run_operator.py` using `.env` (`LLM_GEN_MODELS`, `API_KEYS`, `API_URLS`).

```bash
cp .env.example .env   # set models + keys + URLs

scripts/02-run-adequate-suites.sh \
  --programs-dir programs-v1 \
  --programs-file scripts/pilot-llm-high-equiv.txt
```

Requires sessions from `00`. Per operator: clear Proteum TCs, seed `ts_<OP>/`,
LLM kill attempts with keep-only-if-kills + rollback. Logs under
`<prog>/mutants/adequate-run-logs/`.

**Pilot list:** `scripts/pilot-llm-high-equiv.txt`

Summarize:

```bash
python3 .cursor/skills/mutation-operator-adequate-test-set/scripts/summarize_status.py \
  --program-dir programs-v1/CheckPalindrome
```

---

## `diag-run-one-operator.sh`

Smoke one program/operator (requires `.env`):

```bash
scripts/diag-run-one-operator.sh \
  --program CheckPalindrome --operator u-CRCR --limit 2 --timeout 300
```

---

## Skill: mutation-operator-adequate-test-set

`.cursor/skills/mutation-operator-adequate-test-set/`

| Config | Role |
|--------|------|
| `.env` → `LLM_GEN_MODELS` | Models for successive kill attempts |
| `.env` → `API_KEYS` / `API_URLS` | Length 1 or match models |
| `.env` → `LLM_EQUIV_MODEL` | Equivalence rationality |

Ask Cursor:

```text
Apply mutation-operator-adequate-test-set on programs-v1 with
scripts/pilot-llm-high-equiv.txt. Use .env. Keep tests only when original OK
and target killed; on failure tcase -d -x then exemuta -exec.
```

Details: skill `SKILL.md`, `reference.md`, `PROPOSAL-llm-gen-models.md`.

**Metrics:** unknown token/cost → `null` + `"source": "unavailable"` — never `0`.

Git history marker for the pre-LLM experiment: tag `no-llm-support`.

---

## Research-question analysis (`scripts/analysis/`)

```bash
scripts/analysis/run_rq_analysis.sh programs-v1 programs-v1/_analysis
```
