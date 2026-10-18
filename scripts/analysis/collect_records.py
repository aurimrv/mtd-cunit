#!/usr/bin/env python3
"""Flatten mutants/*_execution_status.json into a tidy CSV of mutant records."""

from __future__ import annotations

import argparse
import csv
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from operator_categories import operator_category


def iter_status_files(programs_dir: Path, programs: list[str] | None):
    roots = []
    if programs:
        roots = [programs_dir / p for p in programs]
    else:
        roots = [p for p in programs_dir.iterdir() if p.is_dir()]
    for root in sorted(roots):
        mutants = root / "mutants"
        if not mutants.is_dir():
            continue
        for path in sorted(mutants.glob("*_execution_status.json")):
            if path.name.startswith("adequate"):
                continue
            yield root.name, path


def load_records(programs_dir: Path, programs: list[str] | None) -> list[dict]:
    rows: list[dict] = []
    for program, path in iter_status_files(programs_dir, programs):
        data = json.loads(path.read_text(encoding="utf-8"))
        op = data.get("operator") or path.name.replace("_execution_status.json", "")
        cat = operator_category(op)
        llm = data.get("llm_name")
        max_iter = data.get("max_iterations")
        for m in data.get("mutants") or []:
            status = m.get("status")
            if status not in ("KILLED", "EQUIVALENT"):
                continue
            attempts = m.get("attempts") or []
            attempt_durs = [
                float(a["duration_ms"])
                for a in attempts
                if a.get("duration_ms") is not None
            ]
            rows.append(
                {
                    "program": program,
                    "operator": op,
                    "category": cat,
                    "mutant_number": int(m["mutant_number"]),
                    "status": status,
                    "killed": 1 if status == "KILLED" else 0,
                    "equivalent": 1 if status == "EQUIVALENT" else 0,
                    "collateral": 1
                    if m.get("killed_by_mutant_target") is not None
                    else 0,
                    "number_of_iterations": int(m.get("number_of_iterations") or 0),
                    "duration_ms": m.get("duration_ms"),
                    "duration_s": (
                        float(m["duration_ms"]) / 1000.0
                        if m.get("duration_ms") is not None
                        else None
                    ),
                    "sum_attempt_duration_ms": sum(attempt_durs) if attempt_durs else None,
                    "llm_name": llm,
                    "max_iterations": max_iter,
                    "function_under_testing": m.get("function_under_testing"),
                    "test_case_number": m.get("test_case_number"),
                    "status_file": str(path),
                }
            )
    return rows


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--programs-dir", required=True)
    p.add_argument(
        "--programs",
        default=None,
        help="Comma-separated program names (default: all subdirs with mutants/)",
    )
    p.add_argument("--out-csv", required=True)
    args = p.parse_args()
    programs = (
        [x.strip() for x in args.programs.split(",") if x.strip()]
        if args.programs
        else None
    )
    rows = load_records(Path(args.programs_dir).resolve(), programs)
    out = Path(args.out_csv)
    out.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        print("error: no records", file=sys.stderr)
        return 1
    with out.open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()))
        w.writeheader()
        w.writerows(rows)
    print(json.dumps({"rows": len(rows), "out_csv": str(out)}))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
