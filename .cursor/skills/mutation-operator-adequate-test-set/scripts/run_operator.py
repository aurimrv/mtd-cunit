#!/usr/bin/env python3
"""
Run the adequate-suite loop for one operator on one program directory.

Automated reuse of ts_data as killing tests is DISABLED. Provide either:
  --candidates-jsonl   LLM-proposed rows, or
  --mutation-oriented-input-generation
      Heuristic synthesizer (no LLM): NEW inputs from Get on: + schema,
      oracles via CUNIT_CAPTURE (not ts_data reuse).
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
from mutation_oriented_input_generation import generate_for_mutant


def run(cmd: list[str], cwd: Path, check: bool = False) -> subprocess.CompletedProcess[str]:
    # Proteum tools sometimes emit non-UTF8 bytes in listings; never crash the loop.
    cp = subprocess.run(
        cmd,
        cwd=str(cwd),
        capture_output=True,
    )

    def _dec(b: bytes | None) -> str:
        return (b or b"").decode("utf-8", errors="replace")

    out = subprocess.CompletedProcess(
        args=cp.args,
        returncode=cp.returncode,
        stdout=_dec(cp.stdout),
        stderr=_dec(cp.stderr),
    )
    if check and out.returncode != 0:
        raise RuntimeError(
            f"cmd failed ({out.returncode}): {cmd}\n{out.stdout}\n{out.stderr}"
        )
    return out


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
            "Typically from an LLM. Optional per-mutant field "
            "equivalence_rationality (or a final line with "
            '{"mutant_id":N,"equivalence_rationality":"..."}) used when marking EQUIVALENT.'
        ),
    )
    p.add_argument(
        "--mutation-oriented-input-generation",
        action="store_true",
        help=(
            "For each alive mutant, heuristically generate NEW cases from Get on:/schema "
            "and CUNIT_CAPTURE oracles (no LLM; does not reuse ts_data rows)."
        ),
    )
    p.add_argument(
        "--resume",
        action="store_true",
        help=(
            "If status JSON already exists, keep it (do not --force init) and "
            "continue remaining alive mutants."
        ),
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    scripts = Path(__file__).resolve().parent
    op = args.operator
    session = args.session
    max_iter = int(args.max_iterations)

    if not args.candidates_jsonl and not args.mutation_oriented_input_generation:
        print(
            "error: automated ts_data reuse is disabled. "
            "Pass --candidates-jsonl with LLM/manual rows, or "
            "--mutation-oriented-input-generation to synthesize mutation-aimed cases.",
            file=sys.stderr,
        )
        return 2

    cand_by_mutant: dict[int, list[dict]] = {}
    equiv_rationality: dict[int, str] = {}
    if args.candidates_jsonl:
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

    status_exists = status_path(program_dir, op).exists()
    resume = bool(args.resume and status_exists)
    # Auto-resume when continuing a crashed operator (alive remain + status present)
    if not resume and args.skip_if_done and status_exists and alive:
        resume = True

    clear_tcases(program_dir, session)
    py(
        scripts,
        "seed_operator_ts.py",
        ["--program-dir", str(program_dir), "--operator", op, "--reset-csv-data"],
        program_dir,
    )
    (program_dir / f"testset_{op}.txt").write_text("", encoding="utf-8")
    init_args = [
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
    ]
    if not resume:
        init_args.append("--force")
    else:
        print(json.dumps({"operator": op, "resume": True, "alive": len(alive)}), flush=True)
    py(scripts, "update_execution_status.py", init_args, program_dir)
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

        start_args = [
            "start-mutant",
            "--program-dir",
            str(program_dir),
            "--operator",
            op,
            "--mutant-id",
            str(target),
        ]
        # Reopened EQUIVALENT mutants need a clean attempt slate
        try:
            st_data = json.loads(status_path(program_dir, op).read_text(encoding="utf-8"))
            for rec in st_data.get("mutants") or []:
                if int(rec.get("mutant_number", -1)) == int(target):
                    if str(rec.get("status") or "").upper() == "EQUIVALENT":
                        start_args.append("--reset")
                    break
        except (OSError, json.JSONDecodeError, TypeError, ValueError):
            pass
        py(scripts, "update_execution_status.py", start_args, program_dir)

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
        if not rows and args.mutation_oriented_input_generation:
            # SSDL needs more branch-hitting probes (equivalents are rare)
            gen_n = max(max_iter, 8) if "ssdl" in op.lower() else max_iter
            try:
                bundle = generate_for_mutant(program_dir, session, target, gen_n)
            except Exception as exc:  # noqa: BLE001 — surface and stop operator
                print(
                    f"error: [{op}] mutation-oriented generation failed for mutant "
                    f"{target}: {exc}",
                    file=sys.stderr,
                    flush=True,
                )
                return 4
            rows = list(bundle.get("candidates") or [])[:gen_n]
            if bundle.get("equivalence_rationality"):
                equiv_rationality[target] = str(bundle["equivalence_rationality"])
            print(
                json.dumps(
                    {
                        "generated": True,
                        "mutant_id": target,
                        "n_candidates": len(rows),
                        "ssdl_boost": gen_n > max_iter,
                    }
                ),
                flush=True,
            )
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
                f"[{op}] no kill candidates for mutant {target}; "
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
            fields_json = json.dumps(cand["fields"]).replace("\x00", "")
            rationality = (
                cand.get("rationality")
                or f"Mutation-oriented case for Get on: {insp.get('get_on')}"
            ).replace("\x00", "")
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
