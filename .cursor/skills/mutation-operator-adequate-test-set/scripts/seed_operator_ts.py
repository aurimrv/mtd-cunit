#!/usr/bin/env python3
"""Create ts_<OP>/ with CSV headers copied from ts_data; touch testset_<OP>.txt."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument(
        "--reset-csv-data",
        action="store_true",
        help="Rewrite CSVs to header-only (destructive)",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    src = program_dir / "ts_data"
    dst = program_dir / f"ts_{args.operator}"
    if not src.is_dir():
        print(f"error: missing {src}", file=sys.stderr)
        return 1

    dst.mkdir(parents=True, exist_ok=True)
    created = []
    skipped = []
    for csv_path in sorted(src.glob("test_cases_*.csv")):
        out = dst / csv_path.name
        header = csv_path.read_text(encoding="utf-8").splitlines()[0]
        if out.exists() and not args.reset_csv_data:
            skipped.append(out.name)
            continue
        out.write_text(header + "\n", encoding="utf-8")
        created.append(out.name)

    testset = program_dir / f"testset_{args.operator}.txt"
    if not testset.exists():
        testset.write_text("", encoding="utf-8")

    print(
        json.dumps(
            {
                "ts_dir": str(dst),
                "testset": str(testset),
                "created_csv": created,
                "skipped_csv": skipped,
            }
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
