#!/usr/bin/env python3
"""Reorder alive mutant IDs in mutants/<OP_ACRONYM>.txt in place."""

from __future__ import annotations

import argparse
import random
import sys
from pathlib import Path


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Reorder mutant IDs per operator under each program's mutants/ "
            "directory. Overwrites each mutants/<OP_ACRONYM>.txt in place "
            "after verifying that no mutant IDs are lost."
        )
    )
    parser.add_argument(
        "--programs-dir",
        required=True,
        type=Path,
        help="Root directory of programs under test (EXPER_HOME)",
    )
    parser.add_argument(
        "--programs-file",
        required=True,
        type=Path,
        help="File listing program directory names (one per line)",
    )
    parser.add_argument(
        "--operators-list",
        required=True,
        type=Path,
        help="Operator list file with OP_CODE,OP_ACRONYM rows",
    )
    parser.add_argument(
        "--order",
        required=True,
        choices=("random", "ascending", "descending"),
        help="Ordering mode for mutant IDs",
    )
    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="RNG seed (required when --order random; ignored otherwise)",
    )
    args = parser.parse_args(argv)

    if args.order == "random" and args.seed is None:
        parser.error("--seed is required when --order random")
    if args.order != "random" and args.seed is not None:
        print(
            f"warning: --seed={args.seed} ignored because --order={args.order}",
            file=sys.stderr,
        )

    return args


def load_programs(programs_file: Path) -> list[str]:
    if not programs_file.is_file():
        raise FileNotFoundError(f"programs file not found: {programs_file}")
    programs: list[str] = []
    for line_no, line in enumerate(programs_file.read_text(encoding="utf-8").splitlines(), 1):
        name = line.strip()
        if not name or name.startswith("#"):
            continue
        programs.append(name)
    if not programs:
        raise ValueError(f"no program names found in {programs_file}")
    return programs


def load_operators(operators_list: Path) -> list[str]:
    if not operators_list.is_file():
        raise FileNotFoundError(f"operators list not found: {operators_list}")
    operators: list[str] = []
    for line_no, line in enumerate(operators_list.read_text(encoding="utf-8").splitlines(), 1):
        raw = line.strip()
        if not raw or raw.startswith("#"):
            continue
        parts = [p.strip() for p in raw.split(",")]
        if len(parts) < 2:
            raise ValueError(
                f"{operators_list}:{line_no}: expected OP_CODE,OP_ACRONYM, got: {raw!r}"
            )
        code, acronym = parts[0], parts[1]
        if line_no == 1 and not code.isdigit():
            # Header row such as OP_NUMBER,OP_Acronym
            continue
        if not code.isdigit():
            raise ValueError(
                f"{operators_list}:{line_no}: OP_CODE must be numeric, got: {code!r}"
            )
        if not acronym:
            raise ValueError(f"{operators_list}:{line_no}: empty OP_ACRONYM")
        operators.append(acronym)
    if not operators:
        raise ValueError(f"no operators found in {operators_list}")
    return operators


def read_mutant_ids(path: Path) -> list[int]:
    ids: list[int] = []
    seen: set[int] = set()
    for line_no, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        text = line.strip()
        if not text:
            continue
        try:
            mid = int(text)
        except ValueError as exc:
            raise ValueError(f"{path}:{line_no}: not an integer mutant ID: {text!r}") from exc
        if mid in seen:
            raise ValueError(f"{path}:{line_no}: duplicate mutant ID {mid}")
        seen.add(mid)
        ids.append(mid)
    return ids


def order_ids(ids: list[int], order: str, rng: random.Random | None) -> list[int]:
    # Normalize to ascending first so --order random --seed N is independent
    # of the current on-disk order.
    ordered = sorted(ids)
    if order == "ascending":
        return ordered
    if order == "descending":
        ordered.sort(reverse=True)
        return ordered
    if order == "random":
        assert rng is not None
        rng.shuffle(ordered)
        return ordered
    raise ValueError(f"unsupported order: {order}")


def assert_no_loss(original: list[int], ordered: list[int], path: Path) -> None:
    if len(ordered) != len(original):
        raise RuntimeError(
            f"{path}: mutant count changed ({len(original)} -> {len(ordered)})"
        )
    if set(ordered) != set(original):
        missing = set(original) - set(ordered)
        extra = set(ordered) - set(original)
        raise RuntimeError(
            f"{path}: mutant ID set changed "
            f"(missing={sorted(missing)}, extra={sorted(extra)})"
        )


def atomic_write_ids(path: Path, ids: list[int]) -> None:
    tmp = path.with_name(path.name + ".tmp")
    content = "".join(f"{mid}\n" for mid in ids)
    tmp.write_text(content, encoding="utf-8")
    tmp.replace(path)


def process_program(
    programs_dir: Path,
    program: str,
    operators: list[str],
    order: str,
    rng: random.Random | None,
) -> int:
    mutants_dir = programs_dir / program / "mutants"
    if not mutants_dir.is_dir():
        raise FileNotFoundError(f"mutants directory not found: {mutants_dir}")

    rewritten = 0
    for acronym in operators:
        path = mutants_dir / f"{acronym}.txt"
        if not path.is_file():
            raise FileNotFoundError(
                f"missing operator file for {program}: {path} "
                "(run 00-create-test-session.sh first)"
            )
        original = read_mutant_ids(path)
        ordered = order_ids(original, order, rng)
        assert_no_loss(original, ordered, path)
        atomic_write_ids(path, ordered)
        rewritten += 1
    return rewritten


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    programs = load_programs(args.programs_file)
    operators = load_operators(args.operators_list)
    rng = random.Random(args.seed) if args.order == "random" else None

    total_files = 0
    for program in programs:
        n = process_program(args.programs_dir, program, operators, args.order, rng)
        total_files += n
        print(f"{program}: reordered {n} operator files ({args.order})")

    print(
        f"Done: {len(programs)} program(s), {total_files} file(s), order={args.order}"
        + (f", seed={args.seed}" if args.order == "random" else "")
    )
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as exc:  # noqa: BLE001 - CLI surface
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1) from exc
