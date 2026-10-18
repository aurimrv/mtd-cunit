#!/usr/bin/env python3
"""
Run one test-generation attempt end-to-end and record metrics.

Appends CSV, validates original runner, imports via tcase, runs exemuta -exec,
checks all alive mutant statuses, and writes the attempt into the status JSON.
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path
from typing import Any

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import (
    alive_path,
    normalize_cost,
    normalize_tokens,
    now_iso,
    parse_muta_listing,
    read_alive_ids,
)
from append_csv_case import format_row, next_test_number, read_header, write_csv_row


def run(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        cmd,
        cwd=str(cwd),
        text=True,
        capture_output=True,
    )


def run_with_tty(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    """Proteum `tcase -add` calls tcgetattr on stdin; needs a TTY."""
    # script(1) allocates a PTY; -q quiet, -e return child exit status (util-linux)
    wrapped = ["script", "-q", "-e", "-c", subprocess.list2cmdline(cmd), "/dev/null"]
    return run(wrapped, cwd=cwd)


def count_tcases(program_dir: Path, session: str) -> int:
    cp = run(["tcase", "-l", session], cwd=program_dir)
    n = 0
    for line in (cp.stdout or "").splitlines():
        if line.startswith("Teste Case #") or line.startswith("Test Case #"):
            n += 1
    return n


def muta_status(program_dir: Path, session: str, mid: int) -> dict[str, Any]:
    cp = run(["muta", "-l", "-f", str(mid), "-t", str(mid), session], cwd=program_dir)
    return parse_muta_listing(cp.stdout or "")


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    p.add_argument("--iteration", type=int, required=True)
    p.add_argument("--function", required=True)
    p.add_argument("--fields-json", required=True)
    p.add_argument("--rationality", required=True)
    p.add_argument("--llm-name", default=None)
    p.add_argument("--tokens-json", default=None, help='JSON or omit for unavailable')
    p.add_argument("--cost-json", default=None, help='JSON or omit for unavailable')
    p.add_argument("--skip-record", action="store_true")
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    operator = args.operator
    session = args.session
    skill_scripts = Path(__file__).resolve().parent

    fields = json.loads(args.fields_json)
    if not isinstance(fields, dict):
        print("error: fields-json must be object", file=sys.stderr)
        return 1

    tokens = normalize_tokens(json.loads(args.tokens_json) if args.tokens_json else None)
    cost = normalize_cost(json.loads(args.cost_json) if args.cost_json else None)

    start_time = now_iso()
    validation = {
        "original_runner_exit_code": None,
        "original_runner_ok": False,
        "tcase_add_ok": False,
        "exemuta_exec_ok": False,
    }
    test_number = None
    proteum_tcase_index = None
    target_life = None
    target_killed = False
    collateral_kills: list[int] = []
    alive_before = read_alive_ids(alive_path(program_dir, operator))

    csv_path = program_dir / f"ts_{operator}" / f"test_cases_{args.function}.csv"
    if not csv_path.exists():
        print(f"error: missing {csv_path}", file=sys.stderr)
        return 1

    header = read_header(csv_path)
    unknown = [k for k in fields if k not in header]
    if unknown:
        print(f"error: unknown columns: {unknown}", file=sys.stderr)
        return 1
    number_col = header.index("test_number")
    test_number = next_test_number(csv_path, number_col)
    write_csv_row(csv_path, format_row(header, fields, test_number))
    testset = program_dir / f"testset_{operator}.txt"
    with testset.open("a", encoding="utf-8") as fh:
        fh.write(f"{args.function} {test_number}\n")

    # Validate original
    cp = run(
        ["./runner", "--data", f"ts_{operator}", args.function, str(test_number)],
        cwd=program_dir,
    )
    validation["original_runner_exit_code"] = cp.returncode
    validation["original_runner_ok"] = cp.returncode == 0
    runner_out = (cp.stdout or "") + (cp.stderr or "")

    if validation["original_runner_ok"]:
        before_n = count_tcases(program_dir, session)
        param = f"--data ts_{operator} {args.function} {test_number}"
        cp = run_with_tty(
            [
                "tcase",
                "-add",
                "-trace",
                "-E",
                "runner",
                "-EE",
                "runner_instr",
                "-p",
                param,
                session,
            ],
            cwd=program_dir,
        )
        after_n = count_tcases(program_dir, session)
        if after_n == before_n + 1:
            validation["tcase_add_ok"] = True
            proteum_tcase_index = after_n
        else:
            validation["tcase_add_ok"] = False
        if validation["tcase_add_ok"]:
            # exemuta -exec also needs a TTY (tcgetattr on stdin)
            cp = run_with_tty(["exemuta", "-exec", "-trace", session], cwd=program_dir)
            validation["exemuta_exec_ok"] = cp.returncode == 0
            check_ids = list(dict.fromkeys(alive_before + [args.mutant_id]))
            for mid in check_ids:
                st = muta_status(program_dir, session, mid)
                if mid == args.mutant_id:
                    target_life = st.get("life")
                    target_killed = bool(st.get("is_dead"))
                elif st.get("is_dead"):
                    collateral_kills.append(mid)

    end_time = now_iso()
    attempt = {
        "iteration": args.iteration,
        "start_time": start_time,
        "end_time": end_time,
        "function_under_testing": args.function,
        "test_case_number": test_number,
        "proteum_tcase_index": proteum_tcase_index,
        "csv_values": fields,
        "rationality": args.rationality,
        "validation": validation,
        "outcome": {
            "target_life": target_life,
            "target_killed": target_killed,
            "collateral_kills": collateral_kills,
        },
        "tokens": tokens,
        "cost_usd": cost,
        "llm_name": args.llm_name,
    }

    if not args.skip_record:
        attempt_path = (
            program_dir
            / "mutants"
            / f".attempt_{operator}_{args.mutant_id}_{args.iteration}.json"
        )
        attempt_path.write_text(json.dumps(attempt, indent=2), encoding="utf-8")
        cp = run(
            [
                sys.executable,
                str(skill_scripts / "update_execution_status.py"),
                "record-attempt",
                "--program-dir",
                str(program_dir),
                "--operator",
                operator,
                "--mutant-id",
                str(args.mutant_id),
                "--attempt-file",
                str(attempt_path),
            ],
            cwd=program_dir,
        )
        if cp.returncode != 0:
            print(cp.stderr, file=sys.stderr)
            return cp.returncode
        try:
            attempt_path.unlink()
        except OSError:
            pass

    summary = dict(attempt)
    summary["runner_ok"] = validation["original_runner_ok"]
    if not validation["original_runner_ok"] and runner_out:
        summary["runner_output_tail"] = runner_out[-500:]
    print(json.dumps(summary, indent=2))
    return 0 if validation["original_runner_ok"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
