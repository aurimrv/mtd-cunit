#!/usr/bin/env python3
"""Create and update mutants/<OP>_execution_status.json with per-attempt metrics."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Any

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import (
    SCHEMA_VERSION,
    VALID_STATUSES,
    aggregate_cost,
    aggregate_tokens,
    duration_ms,
    ensure_mutant,
    empty_cost,
    empty_tokens,
    load_status,
    normalize_cost,
    normalize_tokens,
    now_iso,
    save_status,
    status_path,
)


def cmd_init(args: argparse.Namespace) -> int:
    program_dir = Path(args.program_dir).resolve()
    path = status_path(program_dir, args.operator)
    created = now_iso()
    models = [m.strip() for m in (args.llm_gen_models or "").split(",") if m.strip()]
    if path.exists() and not args.force:
        data = load_status(path)
        if models:
            data["llm_gen_models"] = models
            data["max_attempts"] = len(models)
        if args.llm_equiv_model:
            data["llm_equiv_model"] = args.llm_equiv_model
        data["session"] = args.session
        data["program"] = args.program or program_dir.name
        data["operator"] = args.operator
        data["schema_version"] = SCHEMA_VERSION
        # drop obsolete fields if present
        data.pop("max_iterations", None)
        data.pop("llm_name", None)
        save_status(path, data)
        print(path)
        return 0

    data = {
        "schema_version": SCHEMA_VERSION,
        "program": args.program or program_dir.name,
        "operator": args.operator,
        "session": args.session,
        "llm_gen_models": models,
        "max_attempts": len(models),
        "llm_equiv_model": args.llm_equiv_model or (models[-1] if models else None),
        "created_at": created,
        "updated_at": created,
        "mutants": [],
    }
    save_status(path, data)
    print(path)
    return 0


def cmd_start_mutant(args: argparse.Namespace) -> int:
    program_dir = Path(args.program_dir).resolve()
    path = status_path(program_dir, args.operator)
    if not path.exists():
        print(f"error: missing status JSON: {path}", file=sys.stderr)
        return 1
    data = load_status(path)
    rec = ensure_mutant(data, args.mutant_id)
    if rec.get("initial_time") is None or args.reset:
        rec["initial_time"] = now_iso()
        rec["status"] = "ALIVE"
        rec["end_time"] = None
        rec["duration_ms"] = None
        if args.reset:
            rec["attempts"] = []
            rec["number_of_iterations"] = 0
            rec["tokens_total"] = empty_tokens()
            rec["cost_usd_total"] = empty_cost()
    save_status(path, data)
    print(json.dumps({"mutant_number": rec["mutant_number"], "initial_time": rec["initial_time"]}))
    return 0


def _load_attempt(args: argparse.Namespace) -> dict[str, Any]:
    if args.attempt_file:
        raw = Path(args.attempt_file).read_text(encoding="utf-8")
    else:
        raw = sys.stdin.read()
    attempt = json.loads(raw)
    if not isinstance(attempt, dict):
        raise ValueError("attempt must be a JSON object")
    return attempt


def cmd_record_attempt(args: argparse.Namespace) -> int:
    program_dir = Path(args.program_dir).resolve()
    path = status_path(program_dir, args.operator)
    data = load_status(path)
    rec = ensure_mutant(data, args.mutant_id)
    if rec.get("initial_time") is None:
        rec["initial_time"] = now_iso()

    attempt = _load_attempt(args)
    iteration = int(attempt.get("iteration") or (len(rec["attempts"]) + 1))
    attempt["iteration"] = iteration

    if not attempt.get("start_time"):
        attempt["start_time"] = now_iso()
    if not attempt.get("end_time"):
        attempt["end_time"] = now_iso()
    attempt["duration_ms"] = duration_ms(attempt["start_time"], attempt["end_time"])

    attempt["tokens"] = normalize_tokens(attempt.get("tokens"))
    attempt["cost_usd"] = normalize_cost(attempt.get("cost_usd"))
    if "llm_name" not in attempt:
        attempt["llm_name"] = data.get("llm_name")

    validation = attempt.get("validation") or {}
    attempt["validation"] = {
        "original_runner_exit_code": validation.get("original_runner_exit_code"),
        "original_runner_ok": bool(validation.get("original_runner_ok", False)),
        "tcase_add_ok": bool(validation.get("tcase_add_ok", False)),
        "exemuta_exec_ok": bool(validation.get("exemuta_exec_ok", False)),
    }
    outcome = attempt.get("outcome") or {}
    collateral = outcome.get("collateral_kills") or []
    attempt["outcome"] = {
        "target_life": outcome.get("target_life"),
        "target_killed": bool(outcome.get("target_killed", False)),
        "collateral_kills": [int(x) for x in collateral],
    }

    # Replace same iteration if re-recorded, else append
    replaced = False
    for i, old in enumerate(rec["attempts"]):
        if int(old.get("iteration", -1)) == iteration:
            rec["attempts"][i] = attempt
            replaced = True
            break
    if not replaced:
        rec["attempts"].append(attempt)

    rec["number_of_iterations"] = len(rec["attempts"])
    rec["tokens_total"] = aggregate_tokens(rec["attempts"])
    rec["cost_usd_total"] = aggregate_cost(rec["attempts"])
    rec["status"] = "ALIVE"
    save_status(path, data)
    print(json.dumps({"mutant_number": int(args.mutant_id), "iteration": iteration}))
    return 0


def cmd_finalize_mutant(args: argparse.Namespace) -> int:
    status = args.status.upper()
    if status not in VALID_STATUSES:
        print(f"error: invalid status {status}", file=sys.stderr)
        return 1
    program_dir = Path(args.program_dir).resolve()
    path = status_path(program_dir, args.operator)
    data = load_status(path)
    rec = ensure_mutant(data, args.mutant_id)
    if rec.get("initial_time") is None:
        rec["initial_time"] = now_iso()
    rec["status"] = status
    rec["end_time"] = now_iso()
    rec["duration_ms"] = duration_ms(rec["initial_time"], rec["end_time"])
    rec["number_of_iterations"] = len(rec.get("attempts") or [])
    rec["tokens_total"] = aggregate_tokens(rec.get("attempts") or [])
    rec["cost_usd_total"] = aggregate_cost(rec.get("attempts") or [])

    if args.killed_by_mutant_target is not None:
        rec["killed_by_mutant_target"] = int(args.killed_by_mutant_target)
    elif status == "KILLED" and rec.get("killed_by_mutant_target") is None:
        rec["killed_by_mutant_target"] = None

    if args.function:
        rec["function_under_testing"] = args.function
    if args.test_case_number is not None:
        rec["test_case_number"] = int(args.test_case_number)
    if args.rationality_summary is not None:
        rec["rationality_summary"] = args.rationality_summary

    # If killed by own last successful attempt and fields missing, copy from last attempt
    if status == "KILLED" and rec.get("killed_by_mutant_target") is None:
        for a in reversed(rec.get("attempts") or []):
            if a.get("outcome", {}).get("target_killed"):
                if rec.get("function_under_testing") is None:
                    rec["function_under_testing"] = a.get("function_under_testing")
                if rec.get("test_case_number") is None:
                    rec["test_case_number"] = a.get("test_case_number")
                break

    save_status(path, data)
    print(
        json.dumps(
            {
                "mutant_number": int(args.mutant_id),
                "status": rec["status"],
                "duration_ms": rec["duration_ms"],
                "number_of_iterations": rec["number_of_iterations"],
            }
        )
    )
    return 0


def build_parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__)
    sub = p.add_subparsers(dest="cmd", required=True)

    p_init = sub.add_parser("init", help="Create or refresh status JSON header")
    p_init.add_argument("--program-dir", required=True)
    p_init.add_argument("--operator", required=True)
    p_init.add_argument("--session", required=True)
    p_init.add_argument(
        "--llm-gen-models",
        required=True,
        help="Comma-separated model ids (same as LLM_GEN_MODELS)",
    )
    p_init.add_argument("--llm-equiv-model", default=None)
    p_init.add_argument("--program", default=None)
    p_init.add_argument("--force", action="store_true", help="Replace mutants[] with []")
    p_init.set_defaults(func=cmd_init)

    p_start = sub.add_parser("start-mutant", help="Record initial_time for a mutant")
    p_start.add_argument("--program-dir", required=True)
    p_start.add_argument("--operator", required=True)
    p_start.add_argument("--mutant-id", type=int, required=True)
    p_start.add_argument("--reset", action="store_true")
    p_start.set_defaults(func=cmd_start_mutant)

    p_att = sub.add_parser("record-attempt", help="Append/replace one attempt record")
    p_att.add_argument("--program-dir", required=True)
    p_att.add_argument("--operator", required=True)
    p_att.add_argument("--mutant-id", type=int, required=True)
    p_att.add_argument("--attempt-file", default=None)
    p_att.set_defaults(func=cmd_record_attempt)

    p_fin = sub.add_parser("finalize-mutant", help="Set final status and end_time")
    p_fin.add_argument("--program-dir", required=True)
    p_fin.add_argument("--operator", required=True)
    p_fin.add_argument("--mutant-id", type=int, required=True)
    p_fin.add_argument("--status", required=True)
    p_fin.add_argument("--killed-by-mutant-target", type=int, default=None)
    p_fin.add_argument("--function", default=None)
    p_fin.add_argument("--test-case-number", type=int, default=None)
    p_fin.add_argument("--rationality-summary", default=None)
    p_fin.set_defaults(func=cmd_finalize_mutant)

    return p


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()
    return int(args.func(args))


if __name__ == "__main__":
    raise SystemExit(main())
