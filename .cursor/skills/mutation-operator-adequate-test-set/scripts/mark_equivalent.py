#!/usr/bin/env python3
"""
Mark a mutant as equivalent in Proteum and record it in equivalents_<OP>.txt.

  muta -equiv -x <mutant_id> <session>
  append mutant_id to equivalents_<operator>.txt (deduped, sorted)
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path


def run(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run(cmd, cwd=str(cwd), text=True, capture_output=True)


def equivalents_path(program_dir: Path, operator: str) -> Path:
    return program_dir / f"equivalents_{operator}.txt"


def read_ids(path: Path) -> list[int]:
    if not path.exists():
        return []
    ids: list[int] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        s = line.strip()
        if s.isdigit():
            ids.append(int(s))
    return ids


def write_ids(path: Path, ids: list[int]) -> None:
    uniq = sorted(set(ids))
    path.write_text("".join(f"{i}\n" for i in uniq), encoding="utf-8")


def mark_equivalent(
    program_dir: Path,
    session: str,
    operator: str,
    mutant_id: int,
    *,
    skip_muta: bool = False,
) -> dict:
    mid = int(mutant_id)
    muta_ok = True
    muta_msg = ""
    if not skip_muta:
        cp = run(["muta", "-equiv", "-x", str(mid), session], cwd=program_dir)
        muta_ok = cp.returncode == 0
        muta_msg = ((cp.stdout or "") + (cp.stderr or "")).strip()
        if not muta_ok:
            # Still record the file entry; caller may retry muta
            pass

    path = equivalents_path(program_dir, operator)
    ids = read_ids(path)
    if mid not in ids:
        ids.append(mid)
        write_ids(path, ids)
    else:
        write_ids(path, ids)  # normalize sort/dedupe

    return {
        "mutant_id": mid,
        "operator": operator,
        "session": session,
        "equivalents_file": str(path),
        "muta_ok": muta_ok,
        "muta_message": muta_msg,
        "count_in_file": len(read_ids(path)),
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    p.add_argument(
        "--skip-muta",
        action="store_true",
        help="Only update equivalents_<OP>.txt (no Proteum call)",
    )
    args = p.parse_args()
    result = mark_equivalent(
        Path(args.program_dir).resolve(),
        args.session,
        args.operator,
        args.mutant_id,
        skip_muta=args.skip_muta,
    )
    print(json.dumps(result))
    return 0 if result["muta_ok"] or args.skip_muta else 1


if __name__ == "__main__":
    raise SystemExit(main())
