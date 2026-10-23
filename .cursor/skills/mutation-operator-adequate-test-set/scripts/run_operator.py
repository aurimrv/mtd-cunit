#!/usr/bin/env python3
"""
Run the adequate-suite loop for one operator on one program directory.

Loads LLM_GEN_MODELS / API_KEYS / API_URLS from .env. Each model entry is one
kill attempt. A CSV/Proteum test is kept only if original OK and the target
mutant is killed; otherwise rollback (CSV remove + tcase -d -x + exemuta -exec).
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
from llm_env import load_llm_env
from propose_kill_case import propose_equivalence_rationality, propose_kill_case
from rollback_attempt import rollback


def run(cmd: list[str], cwd: Path, check: bool = False) -> subprocess.CompletedProcess[str]:
    cp = subprocess.run(cmd, cwd=str(cwd), capture_output=True)

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


def py(scripts: Path, name: str, args: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    return run([sys.executable, str(scripts / name), *args], cwd=cwd, check=True)


def clear_tcases(program_dir: Path, session: str) -> None:
    cp = run(["tcase", "-l", session], cwd=program_dir)
    n = sum(
        1
        for line in (cp.stdout or "").splitlines()
        if line.startswith("Teste Case #") or line.startswith("Test Case #")
    )
    if n == 0:
        return
    run(["tcase", "-d", session], cwd=program_dir)


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--operator", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--skip-if-done", action="store_true")
    p.add_argument("--limit-mutants", type=int, default=0, help="0 = all")
    p.add_argument(
        "--resume",
        action="store_true",
        help="Keep existing status JSON and continue remaining alive mutants.",
    )
    p.add_argument(
        "--dotenv-dir",
        default=None,
        help="Directory to search for .env (default: program-dir then parents).",
    )
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    scripts = Path(__file__).resolve().parent
    op = args.operator
    session = args.session

    try:
        llm_cfg = load_llm_env(Path(args.dotenv_dir) if args.dotenv_dir else program_dir)
    except ValueError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2

    alive = read_alive_ids(alive_path(program_dir, op))
    if args.skip_if_done and not alive and status_path(program_dir, op).exists():
        print(json.dumps({"operator": op, "skipped": True, "reason": "done"}))
        return 0
    if not alive:
        print(json.dumps({"operator": op, "skipped": True, "reason": "no_alive"}))
        return 0

    status_exists = status_path(program_dir, op).exists()
    resume = bool(args.resume and status_exists)
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
        "--llm-gen-models",
        ",".join(llm_cfg.models),
        "--llm-equiv-model",
        llm_cfg.equiv_model,
    ]
    if not resume:
        init_args.append("--force")
    else:
        print(
            json.dumps(
                {"operator": op, "resume": True, "alive": len(alive), "models": llm_cfg.models}
            ),
            flush=True,
        )
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

        insp = inspect(program_dir, session, target)
        print(
            json.dumps(
                {
                    "inspection": {
                        "mutant_id": insp["mutant_id"],
                        "detected_function": insp["detected_function"],
                        "get_on": insp["get_on"],
                        "operator": insp.get("operator"),
                    }
                },
                indent=2,
            ),
            flush=True,
        )

        killed = False
        prior_failures: list[dict] = []
        for attempt_i, att in enumerate(llm_cfg.attempts, start=1):
            print(
                json.dumps(
                    {
                        "attempt": attempt_i,
                        "model": att.model,
                        "api_url_host": att.api_url.split("/")[2]
                        if "://" in att.api_url
                        else att.api_url,
                    }
                ),
                flush=True,
            )
            try:
                proposal = propose_kill_case(
                    program_dir=program_dir,
                    session=session,
                    mutant_id=target,
                    model=att.model,
                    api_key=att.api_key,
                    api_url=att.api_url,
                    prior_failures=prior_failures,
                )
            except Exception as exc:  # noqa: BLE001
                print(
                    f"error: [{op}] LLM propose failed for mutant {target} "
                    f"(model={att.model}): {exc}",
                    file=sys.stderr,
                    flush=True,
                )
                prior_failures.append(
                    {"iteration": attempt_i, "error": str(exc), "model": att.model}
                )
                continue

            fields_json = json.dumps(proposal["fields"]).replace("\x00", "")
            rationality = str(proposal.get("rationality") or "").replace("\x00", "")
            tokens_json = json.dumps(proposal.get("tokens") or {})
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
                    str(attempt_i),
                    "--function",
                    proposal["function"],
                    "--fields-json",
                    fields_json,
                    "--rationality",
                    rationality,
                    "--llm-name",
                    att.model,
                    "--tokens-json",
                    tokens_json,
                ],
                cwd=program_dir,
            )
            print(cp.stdout, flush=True)
            try:
                attempt_info = json.loads(cp.stdout or "{}")
            except json.JSONDecodeError:
                attempt_info = {}

            validation = attempt_info.get("validation") or {}
            outcome = attempt_info.get("outcome") or {}
            test_number = attempt_info.get("test_case_number")
            proteum_idx = attempt_info.get("proteum_tcase_index")
            fn = proposal["function"]

            target_killed = bool(outcome.get("target_killed"))
            if target_killed and validation.get("original_runner_ok"):
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
                killed = True
                print(f"[{op}] KILLED mutant {target} with model {att.model}", flush=True)
                break

            # Non-kill or invalid: rollback if anything was added
            rb = rollback(
                program_dir=program_dir,
                operator=op,
                session=session,
                mutant_id=target,
                function=fn,
                test_number=int(test_number) if test_number is not None else None,
                proteum_tcase_index=int(proteum_idx) if proteum_idx is not None else None,
            )
            print(json.dumps({"rollback": rb}), flush=True)
            prior_failures.append(
                {
                    "iteration": attempt_i,
                    "model": att.model,
                    "fields": {
                        k: v
                        for k, v in (proposal.get("fields") or {}).items()
                        if not str(k).startswith("expected")
                    },
                    "original_runner_ok": validation.get("original_runner_ok"),
                    "target_killed": False,
                }
            )

        if not killed and target in read_alive_ids(alive_path(program_dir, op)):
            try:
                er = propose_equivalence_rationality(
                    program_dir=program_dir,
                    session=session,
                    mutant_id=target,
                    model=llm_cfg.equiv_model,
                    api_key=llm_cfg.equiv_api_key,
                    api_url=llm_cfg.equiv_api_url,
                    prior_failures=prior_failures,
                )
            except Exception as exc:  # noqa: BLE001
                print(
                    f"error: [{op}] equivalence LLM failed for mutant {target}: {exc}",
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
                "llm_gen_models": llm_cfg.models,
                "status_json": str(status_path(program_dir, op)),
            }
        ),
        flush=True,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
