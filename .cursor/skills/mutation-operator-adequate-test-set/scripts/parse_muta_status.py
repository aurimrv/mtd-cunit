#!/usr/bin/env python3
"""Parse Proteum `muta -l` output into JSON life status."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _common import parse_muta_listing


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    g = p.add_mutually_exclusive_group(required=True)
    g.add_argument("--stdin", action="store_true", help="Read muta output from stdin")
    g.add_argument("--file", help="Read muta output from file")
    args = p.parse_args()

    if args.stdin:
        text = sys.stdin.read()
    else:
        text = Path(args.file).read_text(encoding="utf-8", errors="replace")

    print(json.dumps(parse_muta_listing(text)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
