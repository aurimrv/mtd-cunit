#!/usr/bin/env python3
"""
Suite-wide audit of CUnit harness oracle anti-patterns (program-agnostic).

Scans */ts_cunit/test_*.c under --programs-dir and reports:
  - empty_oracle: cunit_oracle_check_output("") / ''
  - no_oracle: LLM body (or whole file) has no cunit_oracle_check_* / CU_ASSERT
  - return_only_ignores_buffer: has expected_output check but CSV-like buffer
    column names appear in the test without post-call fingerprinting heuristics

Exit 0 always (report tool). Prints JSON summary to stdout.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ORACLE_RE = re.compile(
    r"cunit_oracle_check_(?:output|stdout)\s*\(|CU_ASSERT|cunit_expect_exit\s*\("
)
EMPTY_ORACLE_RE = re.compile(
    r'cunit_oracle_check_output\s*\(\s*""\s*\)|cunit_oracle_check_output\s*\(\s*\'\'\s*\)'
)
BUFFER_COL_HINTS = (
    "dest",
    "list",
    "pq",
    "arr",
    "a_cell",
    "outset",
    "pat",
    "src",
    "temp",
    "buffer",
    "items",
)
FINGERPRINT_HINTS = (
    "snprintf",
    "fingerprint",
    "for (",
    "strcat",
    "%02x",
    "joined",
)


def _body(text: str) -> str:
    m = re.search(
        r"/\*\s*LLM_BODY_BEGIN\s*\*/(.*?)/\*\s*LLM_BODY_END\s*\*/",
        text,
        re.S,
    )
    return m.group(1) if m else text


def audit_file(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    body = _body(text)
    findings: list[dict] = []
    if EMPTY_ORACLE_RE.search(body) or EMPTY_ORACLE_RE.search(text):
        findings.append({"kind": "empty_oracle", "path": str(path)})
    if not ORACLE_RE.search(body):
        findings.append({"kind": "no_oracle", "path": str(path)})
    # return-only while buffer columns likely present
    has_output_oracle = "cunit_oracle_check_output" in body
    has_buffer_hint = any(h in body for h in BUFFER_COL_HINTS)
    has_fp = any(h in body for h in FINGERPRINT_HINTS)
    # Heuristic: snprintf of a single %d after call is return-only-ish
    single_int = bool(
        re.search(r'snprintf\s*\([^)]*,\s*[^,]*,\s*"%d"', body)
    ) and not has_fp
    if has_output_oracle and has_buffer_hint and (single_int or not has_fp):
        # Avoid double-flagging empty oracle as return_only
        if not EMPTY_ORACLE_RE.search(body):
            findings.append(
                {"kind": "return_only_ignores_buffer", "path": str(path)}
            )
    return findings


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument(
        "--programs-dir",
        action="append",
        required=True,
        help="Root with program subdirs (repeatable)",
    )
    p.add_argument(
        "--only",
        default="",
        help="Comma-separated program names to limit the scan",
    )
    args = p.parse_args()
    only = {x.strip() for x in args.only.split(",") if x.strip()}

    all_findings: list[dict] = []
    for root_s in args.programs_dir:
        root = Path(root_s).resolve()
        for tc in sorted(root.glob("*/ts_cunit/test_*.c")):
            prog = tc.parent.parent.name
            if only and prog not in only:
                continue
            for f in audit_file(tc):
                f["program"] = prog
                f["programs_dir"] = str(root)
                all_findings.append(f)

    by_kind: dict[str, list[dict]] = {}
    for f in all_findings:
        by_kind.setdefault(f["kind"], []).append(f)

    print(
        json.dumps(
            {
                "n_findings": len(all_findings),
                "counts": {k: len(v) for k, v in sorted(by_kind.items())},
                "findings": all_findings,
            },
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
