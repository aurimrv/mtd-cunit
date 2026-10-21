#!/usr/bin/env python3
"""
Inspect a mutant for LLM test invention.

Returns build-view context, Get on:, detected function, and CSV *schema*
from ts_data (headers + one format example). Does NOT propose executable
test cases — the LLM must invent new cases aimed at the mutation.
"""

from __future__ import annotations

import argparse
import csv
import json
import re
import subprocess
import sys
from pathlib import Path

FUN_RE = re.compile(
    r"^(?:BoundedQueue\s*\*|void|int|char\s*\*|double|float|long|unsigned\s+int)\s+"
    r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
    re.MULTILINE,
)


def run(cmd: list[str], cwd: Path) -> str:
    cp = subprocess.run(cmd, cwd=str(cwd), capture_output=True)
    return (cp.stdout or b"").decode("utf-8", errors="replace") + (
        cp.stderr or b""
    ).decode("utf-8", errors="replace")


def build_view_text(program_dir: Path, session: str, mutant_id: int) -> str:
    run(["exemuta", "-build-view", "-x", str(mutant_id), session], cwd=program_dir)
    for name in (f"muta{mutant_id}_{session}", f"muta{mutant_id}_{session}.c"):
        p = program_dir / name
        if p.exists():
            try:
                return p.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
    return ""


def detect_function(view: str, functions: list[str]) -> str | None:
    at = view.find("@")
    head = view if at < 0 else view[:at]
    found = FUN_RE.findall(head)
    for name in reversed(found):
        if name in functions:
            return name
    for name in functions:
        if name in view:
            return name
    return functions[0] if functions else None


def csv_schema(program_dir: Path, function: str) -> dict:
    """Headers + one format-example row from ts_data (not a candidate to reuse)."""
    path = program_dir / "ts_data" / f"test_cases_{function}.csv"
    if not path.exists():
        return {"function": function, "csv_path": str(path), "exists": False}
    with path.open(newline="", encoding="utf-8", errors="replace") as fh:
        reader = csv.DictReader(fh)
        headers = list(reader.fieldnames or [])
        example = next(reader, None)
    format_example = None
    if example:
        format_example = {
            k: v
            for k, v in example.items()
            if k != "test_number"
        }
    return {
        "function": function,
        "csv_path": str(path),
        "exists": True,
        "headers": [h for h in headers if h != "test_number"],
        "format_example_row": format_example,
        "note": (
            "format_example_row is ONLY to illustrate CSV encoding. "
            "Do not reuse it as a killing test; invent a new case for this mutation."
        ),
    }


def inspect(program_dir: Path, session: str, mutant_id: int) -> dict:
    functions = [
        ln.split()[0]
        for ln in (program_dir / "functions.txt").read_text(encoding="utf-8").splitlines()
        if ln.strip()
    ]
    view = build_view_text(program_dir, session, mutant_id)
    fn = detect_function(view, functions) or (functions[0] if functions else None)
    get_on = ""
    operator = ""
    for line in run(
        ["muta", "-l", "-f", str(mutant_id), "-t", str(mutant_id), session],
        cwd=program_dir,
    ).splitlines():
        if "Get on:" in line:
            get_on = line.split("Get on:", 1)[1].strip()
        if "Operator:" in line and "(" in line:
            operator = line[line.find("(") + 1 : line.find(")")]

    schemas = {}
    for f in functions:
        schemas[f] = csv_schema(program_dir, f)

    return {
        "mutant_id": mutant_id,
        "operator": operator,
        "detected_function": fn,
        "get_on": get_on,
        "build_view": view.strip(),
        "functions": functions,
        "csv_schemas": schemas,
        "instruction": (
            "Invent a NEW CUnit CSV row for the detected (or most relevant) function. "
            "Match csv_schemas[function].headers. Use format_example_row only as encoding "
            "reference. Do not reuse it as a killing test. Aim at Get on: / build_view. "
            "Oracle = original ./runner. "
            "If still alive after max_iterations, write an elaborated equivalence "
            "rationality_summary explaining WHY the mutation may be equivalent "
            "(semantics / dead code / unreachable difference), referencing Get on: "
            "and build_view — do NOT only say it survived N attempts."
        ),
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    args = p.parse_args()
    print(
        json.dumps(
            inspect(Path(args.program_dir).resolve(), args.session, args.mutant_id),
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
