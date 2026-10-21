---
name: mutation-operator-adequate-test-set
description: >-
  Builds one adequate CUnit test set per Proteum/IM mutation operator for
  programs under programs-*/ with runner/runner_instr sessions. Records
  precise per-attempt timing and token/cost metrics in
  mutants/<OP>_execution_status.json. Use when creating operator-adequate
  suites, killing alive mutants, running the mutation experiment skill, or
  when the user mentions adequate test sets, max_iterations, or operator
  execution status JSON.
disable-model-invocation: true
---

# Mutation-operator adequate test set

Build an adequate test suite **per mutation operator**: generate CUnit CSV cases
until every mutant in `mutants/<OP>.txt` is KILLED or marked EQUIVALENT after
`max_iterations` failed attempts.

Helpers live in this skill’s `scripts/`. Always use them for status JSON and
alive-list updates so metrics stay consistent.

## Parameters

| Param | Default | Notes |
|-------|---------|-------|
| `--programs-dir` | (required) | e.g. `programs-v1` |
| `--programs-file` | (required) | program names, one per line |
| `--operators-list` | `scripts/unit-operators-list.txt` | `OP_CODE,OP_ACRONYM` |
| `--max-iterations` | **5** | attempts per mutant before EQUIVALENT |
| `--llm-name` | (required for recording) | stored in JSON as-is |

**Override `max_iterations`:** pass `--max-iterations N` in the user prompt, or
state e.g. “use max_iterations=10”. If omitted, use **5**.

## Prerequisites (each program directory)

- `PROTEUMIMHOME` on `PATH` (`exemuta`, `muta`, `tcase`, …)
- Session from `scripts/00-create-test-session.sh`: `S_<PROG>.*`, `runner`, `runner_instr`
- Ordered alive lists from `scripts/01-ordering-alive-mutants.sh`: `mutants/<OP>.txt`
- Baseline CSV schemas in `ts_data/test_cases_*.csv` and `functions.txt`

Prefer an empty Proteum test-case set for a clean operator suite (`tcase -l`
shows none). Disable or delete unrelated TCs if present.

**Session executable name:** `scripts/00-create-test-session.sh` must use
`test-new -E runner` matching `compile_cunit.txt` (`-o runner`). If `-E` and
`-o` disagree, Proteum marks mutants **Anomalous** (compile/link substitution
fails) and they cannot be killed.

## Artifacts

| Path | Role |
|------|------|
| `ts_<OP>/test_cases_<fn>.csv` | Same headers as `ts_data` |
| `testset_<OP>.txt` | Lines: `<function> <test_number>` |
| `mutants/<OP>.txt` | Remaining alive IDs only |
| `mutants/<OP>_execution_status.json` | **Authoritative metrics** |
| `equivalents_<OP>.txt` | Possible-equivalent mutant IDs (one per line); also marked via `muta -equiv` |

## Metrics rules (critical)

1. Record **one attempt object per test-generation try**, even if validation fails
   before `tcase -add`.
2. Timestamps: `date --rfc-3339=ns | tr ' ' T` (ISO-8601 with nanoseconds).
3. `duration_ms` is computed by helpers from start/end — do not invent it.
4. Tokens/cost: if unknown, store **`null`** with `"source": "unavailable"`.
   **Never write `0` for unknown** (zeros falsify experiment totals).
5. Update status JSON **before** removing IDs from `mutants/<OP>.txt`.
6. Collateral kills: finalize those mutants with `killed_by_mutant_target` =
   current target ID; same killing attempt’s `test_case_number` / function.

Full schema: [reference.md](reference.md).

## Helper commands

`SKILL_SCRIPTS` = path to this skill’s `scripts/` directory.

```bash
# Seed ts_<OP>/ headers from ts_data + empty testset_<OP>.txt
python3 "$SKILL_SCRIPTS/seed_operator_ts.py" --program-dir . --operator <OP>

# Init / refresh status JSON header
python3 "$SKILL_SCRIPTS/update_execution_status.py" init \
  --program-dir . --operator <OP> --session S_<PROG> \
  --max-iterations <N> --llm-name "<name>"

# Start work on a mutant (records initial_time)
python3 "$SKILL_SCRIPTS/update_execution_status.py" start-mutant \
  --program-dir . --operator <OP> --mutant-id <ID>

# After each attempt (pass a JSON object on stdin or --attempt-file)
python3 "$SKILL_SCRIPTS/update_execution_status.py" record-attempt \
  --program-dir . --operator <OP> --mutant-id <ID> --attempt-file attempt.json

# Finalize target or collateral
python3 "$SKILL_SCRIPTS/update_execution_status.py" finalize-mutant \
  --program-dir . --operator <OP> --mutant-id <ID> \
  --status KILLED|EQUIVALENT \
  [--killed-by-mutant-target <ID>] \
  [--function <fn>] [--test-case-number <n>] \
  [--rationality-summary "..."]

# Remove finished IDs from alive list (only after JSON finalize)
python3 "$SKILL_SCRIPTS/sync_alive_list.py" \
  --program-dir . --operator <OP> --remove-ids 1,2,3

# Parse muta -l output
python3 "$SKILL_SCRIPTS/parse_muta_status.py" --stdin < muta.out
# → JSON: {"mutant_id":0,"life":"Alive"|"Dead"|"Anomalous"|"Unknown",...}

# Inspect mutant (build-view + CSV schema only — do NOT reuse ts_data rows)
python3 "$SKILL_SCRIPTS/inspect_mutant.py" \
  --program-dir . --session S_<PROG> --mutant-id <ID>

# Append CSV row; prints assigned test_number
python3 "$SKILL_SCRIPTS/append_csv_case.py" \
  --program-dir . --operator <OP> --function <fn> \
  --fields-json '{"maxElements":"3","expected_output":"NONNULL","expected_stdout":""}'

# Preferred: one attempt end-to-end (timestamps + validation + record-attempt)
python3 "$SKILL_SCRIPTS/run_attempt.py" \
  --program-dir . --operator <OP> --session S_<PROG> \
  --mutant-id <ID> --iteration <i> --function <fn> \
  --fields-json '{...}' --rationality "..." --llm-name "<name>"
```

Prefer `run_attempt.py` for every try so attempt metrics stay consistent.


## Algorithm

For each `OP` in the operators list, for each program `P`:

1. `cd <programs-dir>/<P>`
2. Seed `ts_<OP>/`, init status JSON.
3. Select operator only:
   ```bash
   exemuta -select -all 0.0 -<OP> 1.0 S_<P>
   ```
   Example: `exemuta -select -all 0.0 -u-CCDL 1.0 S_boundedQueue`
4. While `mutants/<OP>.txt` has IDs:
   - `target` = first line (list already ordered by script `01`)
   - `start-mutant` for `target`
   - `exemuta -build-view -x <target> S_<P>` and read `muta<target>_S_<P>`
   - Also inspect `muta -l -f <target> -t <target> S_<P>` (`Get on:`)
   - For `iteration` in `1..max_iterations`:
     1. Snapshot `attempt_start` timestamp
     2. Invent a case for a known function; match that CSV’s headers
     3. `append_csv_case.py` → `n`; append `function n` to `testset_<OP>.txt`
     4. Validate original: `./runner --data ts_<OP> <function> <n>`
        - Must exit 0 and CUnit pass. If not: record attempt with
          `original_runner_ok=false`, do **not** `tcase -add`, continue
     5. Import (needs a TTY — `run_attempt.py` wraps with `script`; manually:
        ```bash
        script -q -e -c 'tcase -add -trace -E runner -EE runner_instr \
          -p "--data ts_<OP> <function> <n>" S_<P>' /dev/null
        ```
        )
     6. `exemuta -exec -trace S_<P>`
     7. For every ID still in `mutants/<OP>.txt`, run
        `muta -l -f ID -t ID S_<P>` via `parse_muta_status.py`
        - `Dead` → schedule finalize as KILLED (collateral if ID ≠ target)
     8. `record-attempt` with full metrics (times, validation, outcome, tokens)
     9. If target Dead → `finalize-mutant` KILLED; finalize collaterals;
        `sync_alive_list.py`; break
   - If target still alive after max iterations → mark **possible EQUIVALENT**
     only after writing an **elaborated equivalence rationality** (see below);
     then finalize EQUIVALENT (`muta -equiv -x <id> S_<P>` +
     `equivalents_<OP>.txt`); then `sync_alive_list.py`
5. Next program; then next operator.

## Generating tests (critical)

**Do not copy or reuse rows from `ts_data/` as killing tests.**  
`ts_data` exists only so you can learn the CSV column layout and value encoding
for the CUnit runner. Always generate **new** cases aimed at the current mutant.

**Automated path (no LLM):** `scripts/mutation_oriented_input_generation.py`
(`generate_for_mutant`), invoked via `run_operator.py
--mutation-oriented-input-generation`. It synthesizes inputs from mutant
inspection (Get on: / build-view) + CSV schema and fills oracles with
`CUNIT_CAPTURE`.

**LLM / manual path:** supply `--candidates-jsonl` rows instead.

1. Run `inspect_mutant.py` (build-view, `Get on:`, CSV headers + one format example).
2. Generate a new row for the relevant function using those headers.
3. Oracle = **original** `./runner` (must pass before `tcase -add`).
4. Attempt `rationality` must explain how the case targets **this** mutation
   (`Get on:` / build-view diff).
5. Prefer changing one semantic aspect related to the mutation per attempt.

Forbidden attempt rationality: “Baseline ts_data case…”, “Extra variant…”,
“Cross-function probe…” that merely replay existing `ts_data` rows.

## Equivalence rationality (critical)

Surviving `max_iterations` is **evidence**, not the explanation.

Before `--mark-equivalent` / `finalize-mutant --status EQUIVALENT`, set
`rationality_summary` to a **semantic** argument why this mutant may be
equivalent to the original. Re-read `inspect_mutant.py` output and reason from:

1. **What changed** — quote / paraphrase `Get on:` and the `@…@` fragment.
2. **Why observable behaviour may be identical** — e.g. dead code on reachable
   paths; algebraic identity; redundant check; mutation only affects an
   unreachable branch; same control-flow / return / stdout for all inputs the
   interface can express.
3. **What you already tried** — briefly tie failed attempts to that theory
   (which behaviours you probed), without making “still alive after 5 tests”
   the whole rationale.
4. **Residual doubt** — one sentence: what input class, if any, might still
   kill it but was not expressible or not tried.

**Good (shape):**  
“CCDL replaces `(maxElements < 0)` with `(maxElements)`. For this API, negative
sizes already take the error path in both versions when `maxElements != 0` is
false only for 0; wait — actually for positive sizes the mutant wrongly errors.
…” (think carefully; do not invent false identities.)

**Better example:**  
“Get on: `((q->size) = (q->size))` removes the size decrement on dequeue. That
is *not* equivalent in general (size stays wrong). Marking EQUIVALENT only
because the five invented cases never observed a state where a later
`isEmpty`/`print` assertion was available in the same CSV function; residual
risk: compound scenarios across functions. Possible *tooling* false equivalent,
not a semantic identity.”

**Forbidden equivalence rationality (do not use):**  
- “Alive after 5 attempts; possible equivalent.”  
- “Could not kill after max_iterations.”  
- “Still Alive / no Dead status.”  
- Any summary that only restates the iteration budget.

Pass the elaborated text as `--rationality-summary` to
`finalize_after_attempt.py --mark-equivalent` (or `finalize-mutant`).

## Pilot checklist

```
- [ ] PROTEUMIMHOME set; runner rebuilt if needed
- [ ] Empty or intentional tcase set
- [ ] seed + init status JSON
- [ ] select operator
- [ ] loop until mutants/<OP>.txt empty
- [ ] User reviews mutants/<OP>_execution_status.json
```
