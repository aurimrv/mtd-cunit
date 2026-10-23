#!/usr/bin/env python3
"""Aggregate mutants/*_execution_status.json into a summary CSV + JSON."""

from __future__ import annotations

import argparse
import csv
import json
import sys
from pathlib import Path


def load_all(mutants_dir: Path) -> list[dict]:
    rows = []
    for path in sorted(mutants_dir.glob("*_execution_status.json")):
        data = json.loads(path.read_text(encoding="utf-8"))
        op = data.get("operator") or path.name.replace("_execution_status.json", "")
        mutants = data.get("mutants") or []
        counts = {"KILLED": 0, "EQUIVALENT": 0, "ALIVE": 0, "UNKNOWN": 0}
        attempts = 0
        durations = []
        collateral = 0
        for m in mutants:
            st = m.get("status") or "UNKNOWN"
            counts[st] = counts.get(st, 0) + 1
            attempts += int(m.get("number_of_iterations") or 0)
            if m.get("duration_ms") is not None:
                durations.append(float(m["duration_ms"]))
            if m.get("killed_by_mutant_target") is not None:
                collateral += 1
        rows.append(
            {
                "operator": op,
                "program": data.get("program"),
                "llm_gen_models": data.get("llm_gen_models"),
                "max_attempts": data.get("max_attempts")
                or (
                    len(data["llm_gen_models"])
                    if isinstance(data.get("llm_gen_models"), list)
                    else None
                ),
                "llm_equiv_model": data.get("llm_equiv_model"),
                "mutants_recorded": len(mutants),
                "killed": counts.get("KILLED", 0),
                "equivalent": counts.get("EQUIVALENT", 0),
                "alive": counts.get("ALIVE", 0),
                "unknown": counts.get("UNKNOWN", 0),
                "collateral_kills": collateral,
                "total_attempts": attempts,
                "sum_duration_ms": round(sum(durations), 3) if durations else None,
                "status_file": str(path),
            }
        )
    return rows


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--out-json", default=None)
    p.add_argument("--out-csv", default=None)
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    mutants_dir = program_dir / "mutants"
    rows = load_all(mutants_dir)
    summary = {
        "program": program_dir.name,
        "operators": len(rows),
        "killed": sum(r["killed"] for r in rows),
        "equivalent": sum(r["equivalent"] for r in rows),
        "alive": sum(r["alive"] for r in rows),
        "total_attempts": sum(r["total_attempts"] for r in rows),
        "by_operator": rows,
    }

    out_json = (
        Path(args.out_json)
        if args.out_json
        else program_dir / "mutants" / "adequate-suite-summary.json"
    )
    out_csv = (
        Path(args.out_csv)
        if args.out_csv
        else program_dir / "mutants" / "adequate-suite-summary.csv"
    )
    out_json.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    if rows:
        with out_csv.open("w", newline="", encoding="utf-8") as fh:
            w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()))
            w.writeheader()
            w.writerows(rows)
    print(json.dumps({"out_json": str(out_json), "out_csv": str(out_csv), **{k: summary[k] for k in ("operators", "killed", "equivalent", "alive", "total_attempts")}}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
