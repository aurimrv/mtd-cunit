#!/usr/bin/env python3
"""Remove finished mutant IDs from mutants/<OP>.txt (order-preserving)."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import alive_path, read_alive_ids, write_alive_ids


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument(
        "--remove-ids",
        required=True,
        help="Comma-separated mutant IDs to remove",
    )
    p.add_argument(
        "--strict",
        action="store_true",
        help="Fail if an ID to remove is not present",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    path = alive_path(program_dir, args.operator)
    before = read_alive_ids(path)
    remove = {int(x.strip()) for x in args.remove_ids.split(",") if x.strip()}
    missing = sorted(remove - set(before))
    if missing and args.strict:
        print(f"error: IDs not in alive list: {missing}", file=sys.stderr)
        return 1
    after = [i for i in before if i not in remove]
    write_alive_ids(path, after)
    print(
        json.dumps(
            {
                "path": str(path),
                "removed": sorted(remove & set(before)),
                "missing": missing,
                "remaining": len(after),
            }
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
