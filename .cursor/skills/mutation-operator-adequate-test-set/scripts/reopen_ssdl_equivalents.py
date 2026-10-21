#!/usr/bin/env python3
"""
Reopen false SSDL EQUIVALENT mutants for a fresh mutation-oriented generation pass.

Keeps KILLED results. For each program under --programs-dir whose u-SSDL
equivalent rate is >= --min-equiv-rate:
  1. muta -nequiv on each EQUIVALENT (and leftover ALIVE) mutant
  2. Reset those status JSON rows to ALIVE with empty attempts
  3. Rewrite mutants/u-SSDL.txt with those IDs
  4. Prune equivalents_u-SSDL.txt

Program-agnostic: selects by operator status metrics only.
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import alive_path, empty_cost, empty_tokens, now_iso, status_path, write_alive_ids


def run(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run(cmd, cwd=str(cwd), text=True, capture_output=True)


def load_status(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def equiv_rate(mutants: list[dict]) -> tuple[float, Counter]:
    cc = Counter((m.get("status") or "?").upper() for m in mutants)
    fin = cc["KILLED"] + cc["EQUIVALENT"]
    rate = (cc["EQUIVALENT"] / fin) if fin else 0.0
    return rate, cc


def reopen_program(
    program_dir: Path,
    session: str,
    operator: str,
    *,
    dry_run: bool,
) -> dict:
    st_path = status_path(program_dir, operator)
    if not st_path.exists():
        return {"program": program_dir.name, "skipped": True, "reason": "no_status"}

    data = load_status(st_path)
    mutants = list(data.get("mutants") or [])
    reopen_ids: list[int] = []
    for m in mutants:
        st = str(m.get("status") or "").upper()
        if st in {"EQUIVALENT", "ALIVE"}:
            reopen_ids.append(int(m["mutant_number"]))
    reopen_ids = sorted(set(reopen_ids))
    if not reopen_ids:
        return {
            "program": program_dir.name,
            "skipped": True,
            "reason": "nothing_to_reopen",
        }

    if dry_run:
        return {
            "program": program_dir.name,
            "dry_run": True,
            "reopen": len(reopen_ids),
            "ids_head": reopen_ids[:10],
        }

    # Proteum: clear equivalent flags (batch via -x list chunks)
    chunk = 40
    for i in range(0, len(reopen_ids), chunk):
        part = reopen_ids[i : i + chunk]
        xarg = " ".join(str(x) for x in part)
        cp = run(["muta", "-nequiv", "-x", xarg, session], cwd=program_dir)
        if cp.returncode != 0:
            # Fall back per-id
            for mid in part:
                run(["muta", "-nequiv", "-x", str(mid), session], cwd=program_dir)

    # Status: reset reopened rows; keep KILLED untouched
    reopen_set = set(reopen_ids)
    for m in mutants:
        mid = int(m["mutant_number"])
        if mid not in reopen_set:
            continue
        m["status"] = "ALIVE"
        m["initial_time"] = now_iso()
        m["end_time"] = None
        m["duration_ms"] = None
        m["attempts"] = []
        m["number_of_iterations"] = 0
        m["tokens_total"] = empty_tokens()
        m["cost_usd_total"] = empty_cost()
        m["rationality_summary"] = None
        m["killed_by_mutant_target"] = None
        m["function_under_testing"] = None
        m["test_case_number"] = None
    data["mutants"] = mutants
    st_path.write_text(json.dumps(data, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")

    write_alive_ids(alive_path(program_dir, operator), reopen_ids)

    eq_file = program_dir / "mutants" / f"equivalents_{operator}.txt"
    if eq_file.exists():
        kept = []
        for line in eq_file.read_text(encoding="utf-8").splitlines():
            s = line.strip()
            if not s or not s.isdigit():
                continue
            if int(s) not in reopen_set:
                kept.append(s)
        eq_file.write_text(("\n".join(kept) + ("\n" if kept else "")), encoding="utf-8")

    return {
        "program": program_dir.name,
        "reopened": len(reopen_ids),
        "alive_path": str(alive_path(program_dir, operator)),
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--programs-dir", required=True)
    p.add_argument("--operator", default="u-SSDL")
    p.add_argument(
        "--min-equiv-rate",
        type=float,
        default=0.25,
        help="Reopen when EQUIVALENT/(KILLED+EQUIVALENT) >= this (default 0.25)",
    )
    p.add_argument(
        "--exclude",
        default="",
        help="Comma-separated program names to skip (e.g. replace)",
    )
    p.add_argument(
        "--only",
        default="",
        help="If set, only these comma-separated program names",
    )
    p.add_argument("--dry-run", action="store_true")
    p.add_argument(
        "--list-out",
        default=None,
        help="Write selected program names (one per line) for batch runners",
    )
    args = p.parse_args()

    programs_dir = Path(args.programs_dir).resolve()
    exclude = {x.strip() for x in args.exclude.split(",") if x.strip()}
    only = {x.strip() for x in args.only.split(",") if x.strip()}

    selected: list[str] = []
    reports: list[dict] = []

    for st_path in sorted(programs_dir.glob(f"*/mutants/{args.operator}_execution_status.json")):
        prog_dir = st_path.parent.parent
        name = prog_dir.name
        if name in exclude:
            continue
        if only and name not in only:
            continue
        data = load_status(st_path)
        rate, cc = equiv_rate(list(data.get("mutants") or []))
        fin = cc["KILLED"] + cc["EQUIVALENT"]
        if fin == 0 or rate < args.min_equiv_rate:
            continue
        selected.append(name)
        session = f"S_{name}"
        rep = reopen_program(
            prog_dir, session, args.operator, dry_run=bool(args.dry_run)
        )
        rep["equiv_rate"] = round(rate, 4)
        rep["counts"] = dict(cc)
        reports.append(rep)

    if args.list_out:
        out = Path(args.list_out)
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text("\n".join(selected) + ("\n" if selected else ""), encoding="utf-8")

    print(
        json.dumps(
            {
                "operator": args.operator,
                "min_equiv_rate": args.min_equiv_rate,
                "selected": selected,
                "n_programs": len(selected),
                "reports": reports,
            },
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
