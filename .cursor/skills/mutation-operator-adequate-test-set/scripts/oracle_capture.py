#!/usr/bin/env python3
"""Fill expected_output / expected_stdout via CUNIT_CAPTURE on original runner."""

from __future__ import annotations

import csv
import json
import os
import re
import subprocess
import tempfile
from pathlib import Path

OBS_RE = re.compile(r"CMAGUT_OBS\s+(\{.*\})")
ORACLE_COLS = ("expected_output", "expected_stdout")


def encode_csv_oracle(value: str) -> str:
    if value is None:
        return ""
    s = str(value).replace("\x00", "")
    return (
        s.replace("\\", "\\\\")
        .replace("\n", "\\n")
        .replace("\r", "\\r")
        .replace("\t", "\\t")
    )


def capture_oracles(
    program_dir: Path, function: str, headers: list[str], inputs: dict[str, str]
) -> dict[str, str]:
    oracle_headers = [h for h in headers if h in ORACLE_COLS]
    all_headers = ["test_number"] + [h for h in headers if h != "test_number"]
    for col in ORACLE_COLS:
        if col in headers and col not in all_headers:
            all_headers.append(col)

    with tempfile.TemporaryDirectory(prefix="cmagut_cap_") as tmp:
        tmp_path = Path(tmp)
        row = {"test_number": "1"}
        for h in all_headers:
            if h == "test_number":
                continue
            if h in ORACLE_COLS:
                row[h] = ""
            else:
                row[h] = inputs.get(h, "")
        csv_path = tmp_path / f"test_cases_{function}.csv"
        with csv_path.open("w", newline="", encoding="utf-8") as fh:
            writer = csv.DictWriter(fh, fieldnames=all_headers, extrasaction="ignore")
            writer.writeheader()
            writer.writerow(row)

        env = os.environ.copy()
        env["CUNIT_CAPTURE"] = "1"
        try:
            cp = subprocess.run(
                ["./runner", "--data", str(tmp_path), function, "1"],
                cwd=str(program_dir),
                capture_output=True,
                env=env,
                timeout=20,
            )
        except subprocess.TimeoutExpired:
            result = dict(inputs)
            for col in oracle_headers:
                result[col] = ""
            result["_capture_ok"] = False
            result["_runner_exit"] = -9
            return result

        out = (cp.stdout or b"").decode("utf-8", errors="replace") + (
            cp.stderr or b""
        ).decode("utf-8", errors="replace")
        captured: dict[str, str] = {}
        for line in out.splitlines():
            m = OBS_RE.search(line)
            if not m:
                continue
            try:
                obs = json.loads(m.group(1))
            except json.JSONDecodeError:
                continue
            col = obs.get("column")
            if col in ORACLE_COLS:
                captured[col] = obs.get("value") if obs.get("value") is not None else ""

        result = dict(inputs)
        for col in oracle_headers:
            val = captured.get(col, "")
            if isinstance(val, str):
                val = val.replace("\ufffd", "")
            result[col] = encode_csv_oracle(val if val is not None else "")
        result["_capture_ok"] = bool(captured) or not oracle_headers
        result["_runner_exit"] = cp.returncode
        return result
