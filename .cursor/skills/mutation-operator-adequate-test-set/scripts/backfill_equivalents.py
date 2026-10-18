#!/usr/bin/env python3
"""
For every EQUIVALENT mutant in status JSON: run muta -equiv and refresh
equivalents_<OP>.txt. Safe to re-run (idempotent file updates).
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from mark_equivalent import mark_equivalent, write_ids, equivalents_path


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument(
        "--skip-muta",
        action="store_true",
        help="Only rebuild equivalents_*.txt from status JSON",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    mutants_dir = program_dir / "mutants"
    totals = {"operators": 0, "equivalents": 0, "muta_failures": 0}

    for path in sorted(mutants_dir.glob("*_execution_status.json")):
        if path.name.startswith("adequate"):
            continue
        data = json.loads(path.read_text(encoding="utf-8"))
        op = data.get("operator") or path.name.replace("_execution_status.json", "")
        session = data.get("session") or f"S_{program_dir.name}"
        ids = [
            int(m["mutant_number"])
            for m in (data.get("mutants") or [])
            if m.get("status") == "EQUIVALENT"
        ]
        # Always rewrite file from status truth for this operator
        write_ids(equivalents_path(program_dir, op), ids)
        if not ids:
            continue
        totals["operators"] += 1
        totals["equivalents"] += len(ids)
        if args.skip_muta:
            continue
        for mid in ids:
            info = mark_equivalent(
                program_dir, session, op, mid, skip_muta=False
            )
            if not info["muta_ok"]:
                totals["muta_failures"] += 1
                print(
                    f"warn: muta -equiv failed for {op}#{mid}: {info.get('muta_message')}",
                    file=sys.stderr,
                )

    print(json.dumps({"program": program_dir.name, **totals}, indent=2))
    return 0 if totals["muta_failures"] == 0 else 2


if __name__ == "__main__":
    raise SystemExit(main())
