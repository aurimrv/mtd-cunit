#!/usr/bin/env python3
"""
Finalize target (and collaterals) after a recorded attempt; sync alive list.

Reads the latest attempt outcome from the status JSON for --mutant-id.
If target_killed: status KILLED for target + collaterals.
If --mark-equivalent: status EQUIVALENT for target (no kill), then:
  muta -equiv -x <id> <session>
  append id to equivalents_<OP>.txt
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import find_mutant, load_status, status_path
from mark_equivalent import mark_equivalent


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    p.add_argument("--mark-equivalent", action="store_true")
    p.add_argument("--rationality-summary", default=None)
    p.add_argument(
        "--session",
        default=None,
        help="Proteum session (default: session field in status JSON)",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    scripts = Path(__file__).resolve().parent
    data = load_status(status_path(program_dir, args.operator))
    rec = find_mutant(data, args.mutant_id)
    if rec is None:
        print("error: mutant not in status JSON", file=sys.stderr)
        return 1

    session = args.session or data.get("session")
    attempts = rec.get("attempts") or []
    last = attempts[-1] if attempts else {}
    outcome = last.get("outcome") or {}
    fn = last.get("function_under_testing")
    tc = last.get("test_case_number")
    rationality = args.rationality_summary or last.get("rationality")
    collateral = [int(x) for x in (outcome.get("collateral_kills") or [])]
    remove: list[int] = []
    equiv_info = None

    def run_finalize(mid: int, status: str, killed_by: int | None) -> None:
        cmd = [
            sys.executable,
            str(scripts / "update_execution_status.py"),
            "finalize-mutant",
            "--program-dir",
            str(program_dir),
            "--operator",
            args.operator,
            "--mutant-id",
            str(mid),
            "--status",
            status,
        ]
        if killed_by is not None:
            cmd += ["--killed-by-mutant-target", str(killed_by)]
        if fn is not None:
            cmd += ["--function", str(fn)]
        if tc is not None:
            cmd += ["--test-case-number", str(tc)]
        if rationality is not None and mid == args.mutant_id:
            cmd += ["--rationality-summary", str(rationality)]
        subprocess.check_call(cmd)

    if args.mark_equivalent:
        if not session:
            print("error: session required to mark equivalent in Proteum", file=sys.stderr)
            return 1
        er = (args.rationality_summary or "").strip()
        if not er:
            print(
                "error: --rationality-summary is required when marking EQUIVALENT; "
                "explain WHY the mutation may be equivalent (not only that attempts failed).",
                file=sys.stderr,
            )
            return 1
        er_l = er.lower()
        if len(er) < 80 or (
            ("alive after" in er_l or "still alive" in er_l or "survived" in er_l)
            and "get on" not in er_l
            and "mutat" not in er_l
            and "semantic" not in er_l
            and "equivalent because" not in er_l
            and "identity" not in er_l
            and "unreachable" not in er_l
            and "dead code" not in er_l
        ):
            print(
                "error: equivalence rationality_summary is too weak or missing semantic "
                "content. Discuss the mutation (Get on: / behaviour), not only the "
                "attempt budget. See skill section 'Equivalence rationality'.",
                file=sys.stderr,
            )
            return 1
        run_finalize(args.mutant_id, "EQUIVALENT", None)
        equiv_info = mark_equivalent(
            program_dir, session, args.operator, args.mutant_id
        )
        remove.append(args.mutant_id)
    elif outcome.get("target_killed"):
        run_finalize(args.mutant_id, "KILLED", None)
        remove.append(args.mutant_id)
        for cid in collateral:
            # ensure collateral record exists then finalize
            subprocess.check_call(
                [
                    sys.executable,
                    str(scripts / "update_execution_status.py"),
                    "start-mutant",
                    "--program-dir",
                    str(program_dir),
                    "--operator",
                    args.operator,
                    "--mutant-id",
                    str(cid),
                ]
            )
            run_finalize(cid, "KILLED", args.mutant_id)
            remove.append(cid)
    else:
        print(
            json.dumps(
                {
                    "mutant_id": args.mutant_id,
                    "finalized": False,
                    "target_killed": False,
                    "collateral_kills": collateral,
                }
            )
        )
        return 0

    if remove:
        subprocess.check_call(
            [
                sys.executable,
                str(scripts / "sync_alive_list.py"),
                "--program-dir",
                str(program_dir),
                "--operator",
                args.operator,
                "--remove-ids",
                ",".join(str(x) for x in remove),
            ]
        )

    print(
        json.dumps(
            {
                "mutant_id": args.mutant_id,
                "finalized": True,
                "removed": remove,
                "equivalent": bool(args.mark_equivalent),
                "equivalent_mark": equiv_info,
            }
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
