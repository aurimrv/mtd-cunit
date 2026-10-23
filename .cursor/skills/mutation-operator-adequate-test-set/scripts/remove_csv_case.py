#!/usr/bin/env python3
"""Remove one CSV test row and matching testset_<OP>.txt line by test_number."""

from __future__ import annotations

import argparse
import csv
import io
import json
import sys
from pathlib import Path


def remove_csv_row(csv_path: Path, test_number: int) -> bool:
    if not csv_path.exists():
        return False
    with csv_path.open(newline="", encoding="utf-8") as fh:
        reader = csv.reader(fh)
        header = next(reader, None)
        if not header or "test_number" not in header:
            return False
        idx = header.index("test_number")
        rows = []
        removed = False
        for row in reader:
            if idx < len(row) and row[idx].strip() == str(test_number):
                removed = True
                continue
            rows.append(row)
    if not removed:
        return False
    buf = io.StringIO()
    writer = csv.writer(buf, lineterminator="\n")
    writer.writerow(header)
    for row in rows:
        writer.writerow(row)
    csv_path.write_text(buf.getvalue(), encoding="utf-8")
    return True


def remove_testset_line(testset: Path, function: str, test_number: int) -> bool:
    if not testset.exists():
        return False
    needle = f"{function} {test_number}"
    lines = testset.read_text(encoding="utf-8").splitlines()
    kept = [ln for ln in lines if ln.strip() != needle]
    if len(kept) == len(lines):
        return False
    text = "\n".join(kept)
    if text:
        text += "\n"
    testset.write_text(text, encoding="utf-8")
    return True


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--function", required=True)
    p.add_argument("--test-number", type=int, required=True)
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    csv_path = (
        program_dir / f"ts_{args.operator}" / f"test_cases_{args.function}.csv"
    )
    testset = program_dir / f"testset_{args.operator}.txt"
    ok_csv = remove_csv_row(csv_path, args.test_number)
    ok_ts = remove_testset_line(testset, args.function, args.test_number)
    print(
        json.dumps(
            {
                "csv_removed": ok_csv,
                "testset_removed": ok_ts,
                "function": args.function,
                "test_number": args.test_number,
            }
        )
    )
    return 0 if ok_csv else 1


if __name__ == "__main__":
    raise SystemExit(main())
