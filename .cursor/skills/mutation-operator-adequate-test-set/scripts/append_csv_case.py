#!/usr/bin/env python3
"""Append one test case row to ts_<OP>/test_cases_<function>.csv; print test_number."""

from __future__ import annotations

import argparse
import csv
import io
import json
import sys
from pathlib import Path


def read_header(path: Path) -> list[str]:
    with path.open(newline="", encoding="utf-8") as fh:
        reader = csv.reader(fh)
        header = next(reader, None)
    if not header:
        raise SystemExit(f"error: empty CSV header: {path}")
    return header


def next_test_number(path: Path, number_col: int) -> int:
    max_n = 0
    with path.open(newline="", encoding="utf-8") as fh:
        reader = csv.reader(fh)
        next(reader, None)
        for row in reader:
            if number_col < len(row) and row[number_col].strip().isdigit():
                max_n = max(max_n, int(row[number_col].strip()))
    return max_n + 1


def _encode_oracle_cell(col: str, val: str) -> str:
    """Match CUnit decode of \\n/\\r/\\t; keep CSV single-line for any program."""
    if col not in ("expected_output", "expected_stdout"):
        return val
    # If already escaped (no raw newlines), leave as-is; else escape.
    if "\n" not in val and "\r" not in val and "\t" not in val:
        return val
    return (
        val.replace("\\", "\\\\")
        .replace("\n", "\\n")
        .replace("\r", "\\r")
        .replace("\t", "\\t")
    )


def format_row(header: list[str], fields: dict, test_number: int) -> list[str]:
    row: list[str] = []
    for col in header:
        if col == "test_number":
            row.append(str(test_number))
        elif col in fields:
            val = fields[col]
            if val is None:
                row.append("")
            else:
                row.append(_encode_oracle_cell(col, str(val)))
        else:
            row.append("")
    return row


def write_csv_row(path: Path, row: list[str]) -> None:
    # Use csv module then append; preserve existing file's quoting style lightly
    buf = io.StringIO()
    writer = csv.writer(buf, lineterminator="\n")
    writer.writerow(row)
    line = buf.getvalue()
    with path.open("a", encoding="utf-8") as fh:
        if path.stat().st_size > 0:
            # ensure previous content ends with newline
            with path.open("rb") as rb:
                rb.seek(-1, 2)
                last = rb.read(1)
            if last not in (b"\n", b"\r"):
                fh.write("\n")
        fh.write(line)


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--function", required=True)
    p.add_argument(
        "--fields-json",
        required=True,
        help='JSON object of column→value (excluding test_number), or path via @file',
    )
    p.add_argument(
        "--testset-append",
        action="store_true",
        help="Also append '<function> <n>' to testset_<OP>.txt",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    csv_path = program_dir / f"ts_{args.operator}" / f"test_cases_{args.function}.csv"
    if not csv_path.exists():
        print(f"error: missing {csv_path} (run seed_operator_ts.py first)", file=sys.stderr)
        return 1

    raw = args.fields_json
    if raw.startswith("@"):
        fields = json.loads(Path(raw[1:]).read_text(encoding="utf-8"))
    else:
        fields = json.loads(raw)
    if not isinstance(fields, dict):
        print("error: fields-json must be an object", file=sys.stderr)
        return 1

    header = read_header(csv_path)
    if "test_number" not in header:
        print("error: CSV missing test_number column", file=sys.stderr)
        return 1
    number_col = header.index("test_number")
    unknown = [k for k in fields if k not in header]
    if unknown:
        print(f"error: unknown columns for {args.function}: {unknown}", file=sys.stderr)
        print(f"expected: {header}", file=sys.stderr)
        return 1

    n = next_test_number(csv_path, number_col)
    row = format_row(header, fields, n)
    write_csv_row(csv_path, row)

    if args.testset_append:
        ts_path = program_dir / f"testset_{args.operator}.txt"
        with ts_path.open("a", encoding="utf-8") as fh:
            fh.write(f"{args.function} {n}\n")

    print(
        json.dumps(
            {
                "function": args.function,
                "test_number": n,
                "csv": str(csv_path),
                "row": dict(zip(header, row)),
            }
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
