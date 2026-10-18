#!/usr/bin/env python3
"""
Verify that the union of equivalents_<OP>.txt matches EQUIVALENT entries
in mutants/<OP>_execution_status.json for a program directory.
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path


def ids_from_equiv_files(program_dir: Path) -> dict[str, set[int]]:
    out: dict[str, set[int]] = {}
    for path in sorted(program_dir.glob("equivalents_*.txt")):
        op = path.name[len("equivalents_") : -len(".txt")]
        ids: set[int] = set()
        for line in path.read_text(encoding="utf-8").splitlines():
            s = line.strip()
            if s.isdigit():
                ids.add(int(s))
        out[op] = ids
    return out


def ids_from_status(program_dir: Path) -> dict[str, set[int]]:
    mutants_dir = program_dir / "mutants"
    out: dict[str, set[int]] = {}
    for path in sorted(mutants_dir.glob("*_execution_status.json")):
        if path.name.startswith("adequate"):
            continue
        data = json.loads(path.read_text(encoding="utf-8"))
        op = data.get("operator") or path.name.replace("_execution_status.json", "")
        ids = {
            int(m["mutant_number"])
            for m in (data.get("mutants") or [])
            if m.get("status") == "EQUIVALENT"
        }
        if ids:
            out[op] = ids
    return out


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument(
        "--write-merged",
        default=None,
        help="Optional path to write union of all equivalents_*.txt IDs",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    from_files = ids_from_equiv_files(program_dir)
    from_status = ids_from_status(program_dir)

    merged_files: set[int] = set()
    for ids in from_files.values():
        merged_files |= ids
    merged_status: set[int] = set()
    for ids in from_status.values():
        merged_status |= ids

    ops = sorted(set(from_files) | set(from_status))
    per_op = []
    ok = True
    for op in ops:
        f = from_files.get(op, set())
        s = from_status.get(op, set())
        missing_in_file = sorted(s - f)
        extra_in_file = sorted(f - s)
        match = not missing_in_file and not extra_in_file
        if not match:
            ok = False
        per_op.append(
            {
                "operator": op,
                "in_file": len(f),
                "in_status": len(s),
                "match": match,
                "missing_in_equivalents_file": missing_in_file,
                "extra_in_equivalents_file": extra_in_file,
            }
        )

    if args.write_merged:
        Path(args.write_merged).write_text(
            "".join(f"{i}\n" for i in sorted(merged_files)), encoding="utf-8"
        )

    report = {
        "program": program_dir.name,
        "ok": ok and merged_files == merged_status,
        "merged_equivalents_txt_count": len(merged_files),
        "merged_status_json_equivalent_count": len(merged_status),
        "missing_in_any_equivalents_file": sorted(merged_status - merged_files),
        "extra_in_equivalents_files": sorted(merged_files - merged_status),
        "per_operator": per_op,
    }
    print(json.dumps(report, indent=2))
    return 0 if report["ok"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
