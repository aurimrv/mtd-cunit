#!/usr/bin/env python3
"""
DEPRECATED for automated killing.

ts_data must NOT be reused as killing tests. Use inspect_mutant.py for schema
+ mutation context; the LLM invents new cases.

This script now only prints inspect_mutant output (no candidate list from ts_data).
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from inspect_mutant import inspect


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    p.add_argument("--max-candidates", type=int, default=5)
    args = p.parse_args()
    info = inspect(Path(args.program_dir).resolve(), args.session, args.mutant_id)
    # Keep a stable shape for older callers: empty candidates forces LLM path.
    info["candidates"] = []
    info["max_candidates"] = args.max_candidates
    info["deprecated_notice"] = (
        "No automated candidates. Invent tests with the LLM using this inspection."
    )
    print(json.dumps(info, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
