#!/usr/bin/env python3
"""
Rollback a non-killing (or invalid) attempt:
  remove CSV + testset line → tcase -d -x → exemuta -exec → muta -l
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path
from typing import Any

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import parse_muta_listing
from remove_csv_case import remove_csv_row, remove_testset_line


def run(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    cp = subprocess.run(cmd, cwd=str(cwd), capture_output=True)

    def _dec(b: bytes | None) -> str:
        return (b or b"").decode("utf-8", errors="replace")

    return subprocess.CompletedProcess(
        args=cp.args,
        returncode=cp.returncode,
        stdout=_dec(cp.stdout),
        stderr=_dec(cp.stderr),
    )


def run_tty(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    wrapped = ["script", "-q", "-e", "-c", subprocess.list2cmdline(cmd), "/dev/null"]
    return run(wrapped, cwd=cwd)


def rollback(
    *,
    program_dir: Path,
    operator: str,
    session: str,
    mutant_id: int,
    function: str,
    test_number: int | None,
    proteum_tcase_index: int | None,
) -> dict[str, Any]:
    csv_path = program_dir / f"ts_{operator}" / f"test_cases_{function}.csv"
    testset = program_dir / f"testset_{operator}.txt"

    csv_removed = False
    testset_removed = False
    if test_number is not None:
        csv_removed = remove_csv_row(csv_path, test_number)
        testset_removed = remove_testset_line(testset, function, test_number)

    tcase_deleted = False
    if proteum_tcase_index is not None and proteum_tcase_index > 0:
        cp = run_tty(
            ["tcase", "-d", "-x", str(proteum_tcase_index), session],
            cwd=program_dir,
        )
        tcase_deleted = cp.returncode == 0

    mid = str(mutant_id)
    cp_exec = run_tty(
        ["exemuta", "-exec", "-trace", "-f", mid, "-t", mid, session],
        cwd=program_dir,
    )
    cp_muta = run(["muta", "-l", "-f", mid, "-t", mid, session], cwd=program_dir)
    life = parse_muta_listing(cp_muta.stdout or "")

    return {
        "csv_removed": csv_removed,
        "testset_removed": testset_removed,
        "tcase_deleted": tcase_deleted,
        "proteum_tcase_index": proteum_tcase_index,
        "exemuta_exec_ok": cp_exec.returncode == 0,
        "mutant_id": mutant_id,
        "life_after_rollback": life.get("life"),
        "is_dead_after_rollback": bool(life.get("is_dead")),
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    p.add_argument("--function", required=True)
    p.add_argument("--test-number", type=int, default=None)
    p.add_argument("--proteum-tcase-index", type=int, default=None)
    args = p.parse_args()

    info = rollback(
        program_dir=Path(args.program_dir).resolve(),
        operator=args.operator,
        session=args.session,
        mutant_id=args.mutant_id,
        function=args.function,
        test_number=args.test_number,
        proteum_tcase_index=args.proteum_tcase_index,
    )
    print(json.dumps(info, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
