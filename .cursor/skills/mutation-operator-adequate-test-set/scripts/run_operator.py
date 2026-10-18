#!/usr/bin/env python3
"""
Run the adequate-suite loop for one operator on one program directory.

Automated reuse of ts_data as killing tests is DISABLED. Use the Cursor skill
with an LLM that invents mutation-specific cases (see inspect_mutant.py).

This driver remains useful for session select / seed / finalize plumbing when
driven by an external inventor that supplies --candidate-file JSON lines.
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import alive_path, read_alive_ids, status_path
from inspect_mutant import inspect


def run(cmd: list[str], cwd: Path, check: bool = False) -> subprocess.CompletedProcess[str]:
    cp = subprocess.run(cmd, cwd=str(cwd), text=True, capture_output=True)
    if check and cp.returncode != 0:
        raise RuntimeError(
            f"cmd failed ({cp.returncode}): {cmd}\n{cp.stdout}\n{cp.stderr}"
        )
    return cp


def run_tty(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    wrapped = ["script", "-q", "-e", "-c", subprocess.list2cmdline(cmd), "/dev/null"]
    return run(wrapped, cwd=cwd)


def clear_tcases(program_dir: Path, session: str) -> None:
    # Delete all test cases if any exist
    cp = run(["tcase", "-l", session], cwd=program_dir)
    n = sum(
        1
        for line in (cp.stdout or "").splitlines()
        if line.startswith("Teste Case #") or line.startswith("Test Case #")
    )
    if n == 0:
        return
    run(["tcase", "-d", session], cwd=program_dir)


def py(scripts: Path, name: str, args: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    return run([sys.executable, str(scripts / name), *args], cwd=cwd, check=True)


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--max-iterations", type=int, default=5)
    p.add_argument("--llm-name", default="composer-automated-proposer")
    p.add_argument("--skip-if-done", action="store_true")
    p.add_argument("--limit-mutants", type=int, default=0, help="0 = all")
    p.add_argument(
        "--candidates-jsonl",
        default=None,
        help=(
            "JSONL file: each line is "
            '{"mutant_id":N,"iteration":i,"function":"...","fields":{...},"rationality":"..."} '
            "Invented by the LLM (required). Optional per-mutant field "
            "equivalence_rationality (or a final line with "
            '{"mutant_id":N,"equivalence_rationality":"..."}) used when marking EQUIVALENT. '
            "Without this file, the driver refuses to invent from ts_data."
        ),
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    scripts = Path(__file__).resolve().parent
    op = args.operator
    session = args.session
    max_iter = int(args.max_iterations)

    if not args.candidates_jsonl:
        print(
            "error: automated ts_data reuse is disabled. "
            "Apply the mutation-operator-adequate-test-set skill so the LLM invents "
            "cases (inspect_mutant.py → run_attempt.py), or pass --candidates-jsonl "
            "with LLM-invented rows.",
            file=sys.stderr,
        )
        return 2

    cand_by_mutant: dict[int, list[dict]] = {}
    equiv_rationality: dict[int, str] = {}
    with Path(args.candidates_jsonl).open(encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if not line:
                continue
            row = json.loads(line)
            mid = int(row["mutant_id"])
            if row.get("equivalence_rationality"):
                equiv_rationality[mid] = str(row["equivalence_rationality"])
            if row.get("fields") and row.get("function"):
                cand_by_mutant.setdefault(mid, []).append(row)

    alive = read_alive_ids(alive_path(program_dir, op))
    if args.skip_if_done and not alive and status_path(program_dir, op).exists():
        print(json.dumps({"operator": op, "skipped": True, "reason": "done"}))
        return 0
    if not alive:
        print(json.dumps({"operator": op, "skipped": True, "reason": "no_alive"}))
        return 0

    clear_tcases(program_dir, session)
    py(
        scripts,
        "seed_operator_ts.py",
        ["--program-dir", str(program_dir), "--operator", op, "--reset-csv-data"],
        program_dir,
    )
    (program_dir / f"testset_{op}.txt").write_text("", encoding="utf-8")
    py(
        scripts,
        "update_execution_status.py",
        [
            "init",
            "--program-dir",
            str(program_dir),
            "--operator",
            op,
            "--session",
            session,
            "--max-iterations",
            str(max_iter),
            "--llm-name",
            args.llm_name,
            "--force",
        ],
        program_dir,
    )
    run(["exemuta", "-select", "-all", "0.0", f"-{op}", "1.0", session], cwd=program_dir)

    processed = 0
    while True:
        alive = read_alive_ids(alive_path(program_dir, op))
        if not alive:
            break
        if args.limit_mutants and processed >= args.limit_mutants:
            break
        target = alive[0]
        processed += 1
        print(f"[{op}] target={target} remaining={len(alive)}", flush=True)

        py(
            scripts,
            "update_execution_status.py",
            [
                "start-mutant",
                "--program-dir",
                str(program_dir),
                "--operator",
                op,
                "--mutant-id",
                str(target),
            ],
            program_dir,
        )

        # Always dump inspection for logging / LLM context
        insp = inspect(program_dir, session, target)
        print(json.dumps({"inspection": {
            "mutant_id": insp["mutant_id"],
            "detected_function": insp["detected_function"],
            "get_on": insp["get_on"],
            "operator": insp.get("operator"),
        }}, indent=2), flush=True)

        rows = sorted(
            cand_by_mutant.get(target, []),
            key=lambda r: int(r.get("iteration") or 0),
        )[:max_iter]
        if not rows:
            er = equiv_rationality.get(target)
            if not er:
                print(
                    f"error: [{op}] mutant {target} has no candidates and no "
                    f"equivalence_rationality. Provide an elaborated semantic reason "
                    f"(not merely 'no tests').",
                    file=sys.stderr,
                    flush=True,
                )
                return 3
            print(
                f"[{op}] no LLM kill candidates for mutant {target}; "
                f"marking EQUIVALENT with provided rationality",
                flush=True,
            )
            run(
                [
                    sys.executable,
                    str(scripts / "finalize_after_attempt.py"),
                    "--program-dir",
                    str(program_dir),
                    "--operator",
                    op,
                    "--mutant-id",
                    str(target),
                    "--mark-equivalent",
                    "--rationality-summary",
                    er,
                ],
                cwd=program_dir,
                check=True,
            )
            continue

        killed = False
        for cand in rows:
            i = int(cand.get("iteration") or 1)
            fields_json = json.dumps(cand["fields"])
            rationality = cand.get("rationality") or (
                f"LLM-invented case for Get on: {insp.get('get_on')}"
            )
            cp = run(
                [
                    sys.executable,
                    str(scripts / "run_attempt.py"),
                    "--program-dir",
                    str(program_dir),
                    "--operator",
                    op,
                    "--session",
                    session,
                    "--mutant-id",
                    str(target),
                    "--iteration",
                    str(i),
                    "--function",
                    cand["function"],
                    "--fields-json",
                    fields_json,
                    "--rationality",
                    rationality,
                    "--llm-name",
                    args.llm_name,
                ],
                cwd=program_dir,
            )
            print(cp.stdout, flush=True)
            if cp.returncode not in (0, 2):
                print(cp.stderr, file=sys.stderr, flush=True)

            fin = run(
                [
                    sys.executable,
                    str(scripts / "finalize_after_attempt.py"),
                    "--program-dir",
                    str(program_dir),
                    "--operator",
                    op,
                    "--mutant-id",
                    str(target),
                    "--rationality-summary",
                    rationality,
                ],
                cwd=program_dir,
            )
            print(fin.stdout, flush=True)
            try:
                info = json.loads(fin.stdout or "{}")
            except json.JSONDecodeError:
                info = {}
            if info.get("finalized") and not info.get("equivalent"):
                killed = True
                break
            if target not in read_alive_ids(alive_path(program_dir, op)):
                killed = True
                break

        if not killed and target in read_alive_ids(alive_path(program_dir, op)):
            er = equiv_rationality.get(target)
            if not er:
                print(
                    f"error: [{op}] mutant {target} still alive after {len(rows)} attempts "
                    f"but equivalence_rationality is missing. The LLM must explain WHY the "
                    f"mutation may be equivalent (Get on: / semantics), not only that it "
                    f"survived {len(rows)} attempts.",
                    file=sys.stderr,
                    flush=True,
                )
                return 3
            weak = (
                "alive after" in er.lower()
                or "max_iterations" in er.lower()
                or "still alive" in er.lower()
            ) and len(er) < 120
            if weak:
                print(
                    f"error: [{op}] mutant {target} equivalence_rationality looks too weak "
                    f"(iteration-budget only). Elaborate semantic reason. Got: {er!r}",
                    file=sys.stderr,
                    flush=True,
                )
                return 3
            run(
                [
                    sys.executable,
                    str(scripts / "finalize_after_attempt.py"),
                    "--program-dir",
                    str(program_dir),
                    "--operator",
                    op,
                    "--mutant-id",
                    str(target),
                    "--mark-equivalent",
                    "--rationality-summary",
                    er,
                ],
                cwd=program_dir,
                check=True,
            )
            print(f"[{op}] marked EQUIVALENT mutant {target}", flush=True)

    remaining = read_alive_ids(alive_path(program_dir, op))
    print(
        json.dumps(
            {
                "operator": op,
                "processed_targets": processed,
                "remaining_alive": len(remaining),
                "status_json": str(status_path(program_dir, op)),
            }
        ),
        flush=True,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
