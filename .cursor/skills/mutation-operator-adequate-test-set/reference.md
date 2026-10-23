# Reference: operator-adequate status JSON and conventions

## Status JSON path

`mutants/<OP_ACRONYM>_execution_status.json` — one file per operator per program.

## Schema (`schema_version`: 1)

```json
{
  "schema_version": 1,
  "program": "boundedQueue",
  "operator": "u-CCDL",
  "session": "S_boundedQueue",
  "llm_gen_models": ["gpt-4o-mini", "gpt-4o-mini"],
  "max_attempts": 2,
  "llm_equiv_model": "gpt-4o-mini",
  "created_at": "2026-10-17T21:00:00.000000000+01:00",
  "updated_at": "2026-10-17T21:10:00.000000000+01:00",
  "mutants": [
    {
      "mutant_number": 823,
      "status": "KILLED",
      "killed_by_mutant_target": null,
      "function_under_testing": "printBoundedQueue",
      "test_case_number": 1,
      "rationality_summary": "Size≥2 prints separators; CCDL widens comma condition.",
      "initial_time": "2026-10-17T21:01:00.000000000+01:00",
      "end_time": "2026-10-17T21:02:00.000000000+01:00",
      "duration_ms": 60000.0,
      "number_of_iterations": 1,
      "attempts": [
        {
          "iteration": 1,
          "start_time": "2026-10-17T21:01:00.000000000+01:00",
          "end_time": "2026-10-17T21:02:00.000000000+01:00",
          "duration_ms": 60000.0,
          "function_under_testing": "printBoundedQueue",
          "test_case_number": 1,
          "proteum_tcase_index": 1,
          "csv_values": {
            "q": "cap=3|init=1,2,3",
            "expected_output": "",
            "expected_stdout": "[1, 2, 3]"
          },
          "rationality": "Mutant uses (i < q->size); trailing comma → stdout mismatch.",
          "validation": {
            "original_runner_exit_code": 0,
            "original_runner_ok": true,
            "tcase_add_ok": true,
            "exemuta_exec_ok": true
          },
          "outcome": {
            "target_life": "Dead",
            "target_killed": true,
            "collateral_kills": []
          },
          "tokens": { "input": null, "output": null, "source": "unavailable" },
          "cost_usd": {
            "input": null,
            "output": null,
            "total": null,
            "source": "unavailable"
          },
          "llm_name": "gpt-4o-mini"
        }
      ],
      "tokens_total": { "input": null, "output": null, "source": "unavailable" },
      "cost_usd_total": {
        "input": null,
        "output": null,
        "total": null,
        "source": "unavailable"
      }
    }
  ]
}
```

### Status values

| `status` | Meaning |
|----------|---------|
| `KILLED` | Proteum life is Dead (or treated as killed) |
| `EQUIVALENT` | Possible equivalent after `LLM_GEN_MODELS` is exhausted. Stored in `equivalents_<OP>.txt` and registered with `muta -equiv`. **`rationality_summary` must be semantic** (see SKILL.md), not merely “survived N attempts”. |
| `ALIVE` | Work in progress |
| `UNKNOWN` | Could not determine |

### Equivalence `rationality_summary` checklist

Must include: (1) what the mutation changes, (2) why behaviour may match the
original on reachable / expressible behaviours, (3) how prior attempts relate
to that theory, (4) residual doubt. Must **not** be only “still alive after N attempts”.

### Collateral

When mutant `Y` dies while targeting `X`:

- `Y.status` = `KILLED`
- `Y.killed_by_mutant_target` = `X`
- `Y.function_under_testing` / `test_case_number` = the attempt that killed it
- `Y.attempts` may be empty; totals still filled if known
- Attempt on `X` lists `Y` in `outcome.collateral_kills`

### Token / cost aggregation

`tokens_total` / `cost_usd_total` on a mutant:

- Sum numeric attempt fields when **every** contributing attempt has `source != "unavailable"` and non-null values
- Otherwise `null` with `"source": "unavailable"` or `"source": "partial"` if some attempts reported and some did not

Never coerce missing values to `0`.

## CSV / testset conventions

- Directory: `ts_<OP>/`
- Files: `test_cases_<function>.csv` — header copied from `ts_data/test_cases_<function>.csv`
- First column: `test_number` (integer, assigned by `append_csv_case.py`)
- `testset_<OP>.txt`: one line per imported case: `<function> <test_number>`
- Runner: `./runner --data ts_<OP> <function> <test_number>`
- Proteum import params: `--data ts_<OP> <function> <test_number>`

### Queue value encoding (`q` column)

Examples from `ts_data`:

- `cap=3|init=` — empty queue capacity 3
- `cap=3|init=1,2` — two elements
- `cap=3|init=1,2,3|deq=1` — enqueue then dequeue once
- Quoted when commas appear: `"cap=2|init=1,2"`

### Pointer / output expectations

- `expected_output`: numeric, empty, `NULL`, or `NONNULL` as used by the program’s CUnit tests
- `expected_stdout`: exact stdout string (may include `\n` as two characters in CSV or real newlines per existing files)

## `muta -l` status parsing

Typical lines:

```text
MUTANT # 823
	Status Alive Active
	Causa Mortis: None - Test Case -1
```

After kill:

```text
	Status Dead Active
	Causa Mortis: ... - Test Case N
```

`parse_muta_status.py` maps the first life token after `Status` to
`Alive` | `Dead` | `Anomalous` | `Unknown`.

Treat **`Dead` as killed**. `Anomalous` means Proteum failed to produce an
executable (often `-E` / `-o` name mismatch in the session). Do **not** invent
more tests for a true compile anomaly; fix the session and re-run. If a mutant
flips to Anomalous mid-run after a broken `exemuta -exec` (e.g. missing TTY),
clear with `muta -nanomalous -f ID -t ID S_<P>` after fixing the environment,
then re-exec.

## Proteum select / exec

```bash
exemuta -select -all 0.0 -u-CCDL 1.0 S_boundedQueue
exemuta -build-view -x 823 S_boundedQueue
# reads muta823_S_boundedQueue (and .c twin)
exemuta -exec -trace S_boundedQueue
muta -l -f 823 -t 823 S_boundedQueue
```

## Attempt budget: `LLM_GEN_MODELS`

Configure in repo-root `.env` (see PROPOSAL-llm-gen-models.md):

```bash
LLM_GEN_MODELS=model_a,model_b,model_a
API_KEYS=key_for_all
API_URLS=https://api.example.com/v1
LLM_EQUIV_MODEL=model_a
```

- `LLM_GEN_MODELS` **length** = number of kill attempts per mutant.
- `API_KEYS` / `API_URLS`: length **1** (broadcast) or **same length** as models.
- Status JSON stores `llm_gen_models` / `max_attempts`; each attempt records `llm_name`.
  Never store raw API keys.

## Keep / rollback rules

A case stays in `ts_<OP>/` and in the Proteum session only if:

1. Original `./runner` exits 0, and  
2. `muta -l` shows the **target** mutant Dead after `exemuta -exec`.

Otherwise:

1. Remove the CSV row and `testset_<OP>.txt` line.  
2. `tcase -d -x <proteum_tcase_index> S_<PROG>`  
3. **`exemuta -exec -f <id> -t <id> S_<PROG>`** — required so kill marks match the suite after deletion.  
4. Re-check `muta -l` (expect Alive before the next attempt).

## Proteum delete + re-exec

```bash
tcase -d -x <proteum_index> S_<PROG>
exemuta -exec -trace -f <mutant_id> -t <mutant_id> S_<PROG>
muta -l -f <mutant_id> -t <mutant_id> S_<PROG>
```
