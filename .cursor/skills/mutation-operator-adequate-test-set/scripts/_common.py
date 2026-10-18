"""Shared helpers for operator-adequate status JSON."""

from __future__ import annotations

import json
import os
import re
import subprocess
import tempfile
from datetime import datetime, timezone
from pathlib import Path
from typing import Any


SCHEMA_VERSION = 1
VALID_STATUSES = frozenset({"KILLED", "EQUIVALENT", "ALIVE", "UNKNOWN"})


def now_iso() -> str:
    """ISO-8601 timestamp with nanoseconds, matching `date --rfc-3339=ns | tr ' ' T`."""
    try:
        out = subprocess.check_output(
            ["date", "--rfc-3339=ns"], text=True
        ).strip()
        return out.replace(" ", "T", 1)
    except (OSError, subprocess.CalledProcessError):
        return datetime.now(timezone.utc).isoformat()


def parse_iso(ts: str) -> datetime:
    s = ts.strip()
    if " " in s and "T" not in s:
        s = s.replace(" ", "T", 1)
    # Support 1–9 fractional digits
    if "." in s:
        head, rest = s.split(".", 1)
        frac = ""
        tz = ""
        for i, ch in enumerate(rest):
            if ch.isdigit():
                frac += ch
            else:
                tz = rest[i:]
                break
        else:
            tz = ""
        frac = (frac + "000000")[:6]  # datetime supports microseconds
        s = f"{head}.{frac}{tz}"
    if s.endswith("Z"):
        s = s[:-1] + "+00:00"
    return datetime.fromisoformat(s)


def duration_ms(start: str | None, end: str | None) -> float | None:
    if not start or not end:
        return None
    try:
        delta = parse_iso(end) - parse_iso(start)
        return delta.total_seconds() * 1000.0
    except (TypeError, ValueError):
        return None


def status_path(program_dir: Path, operator: str) -> Path:
    return program_dir / "mutants" / f"{operator}_execution_status.json"


def alive_path(program_dir: Path, operator: str) -> Path:
    return program_dir / "mutants" / f"{operator}.txt"


def atomic_write_json(path: Path, data: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    text = json.dumps(data, indent=2, ensure_ascii=False) + "\n"
    fd, tmp_name = tempfile.mkstemp(
        dir=str(path.parent), prefix=f".{path.name}.", suffix=".tmp"
    )
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as fh:
            fh.write(text)
            fh.flush()
            os.fsync(fh.fileno())
        os.replace(tmp_name, path)
    except Exception:
        try:
            os.unlink(tmp_name)
        except OSError:
            pass
        raise


def load_status(path: Path) -> dict[str, Any]:
    with path.open(encoding="utf-8") as fh:
        return json.load(fh)


def save_status(path: Path, data: dict[str, Any]) -> None:
    data["updated_at"] = now_iso()
    atomic_write_json(path, data)


def find_mutant(data: dict[str, Any], mutant_id: int) -> dict[str, Any] | None:
    for m in data.get("mutants", []):
        if int(m["mutant_number"]) == int(mutant_id):
            return m
    return None


def ensure_mutant(data: dict[str, Any], mutant_id: int) -> dict[str, Any]:
    existing = find_mutant(data, mutant_id)
    if existing is not None:
        return existing
    record = {
        "mutant_number": int(mutant_id),
        "status": "ALIVE",
        "killed_by_mutant_target": None,
        "function_under_testing": None,
        "test_case_number": None,
        "rationality_summary": None,
        "initial_time": None,
        "end_time": None,
        "duration_ms": None,
        "number_of_iterations": 0,
        "attempts": [],
        "tokens_total": empty_tokens(),
        "cost_usd_total": empty_cost(),
    }
    data.setdefault("mutants", []).append(record)
    return record


def empty_tokens(source: str = "unavailable") -> dict[str, Any]:
    return {"input": None, "output": None, "source": source}


def empty_cost(source: str = "unavailable") -> dict[str, Any]:
    return {
        "input": None,
        "output": None,
        "total": None,
        "source": source,
    }


def normalize_tokens(obj: Any) -> dict[str, Any]:
    if not isinstance(obj, dict):
        return empty_tokens()
    src = obj.get("source")
    inp = obj.get("input")
    out = obj.get("output")
    if inp is None and out is None:
        return empty_tokens(src or "unavailable")
    if src is None:
        src = "reported"
    return {"input": inp, "output": out, "source": src}


def normalize_cost(obj: Any) -> dict[str, Any]:
    if not isinstance(obj, dict):
        return empty_cost()
    src = obj.get("source")
    inp = obj.get("input")
    out = obj.get("output")
    total = obj.get("total")
    if inp is None and out is None and total is None:
        return empty_cost(src or "unavailable")
    if src is None:
        src = "reported"
    if total is None and inp is not None and out is not None:
        try:
            total = float(inp) + float(out)
        except (TypeError, ValueError):
            total = None
    return {"input": inp, "output": out, "total": total, "source": src}


def aggregate_tokens(attempts: list[dict[str, Any]]) -> dict[str, Any]:
    if not attempts:
        return empty_tokens()
    sources = []
    inputs: list[float] = []
    outputs: list[float] = []
    for a in attempts:
        t = normalize_tokens(a.get("tokens"))
        sources.append(t["source"])
        if t["source"] == "unavailable" or t["input"] is None or t["output"] is None:
            continue
        inputs.append(float(t["input"]))
        outputs.append(float(t["output"]))
    if len(inputs) == 0:
        return empty_tokens("unavailable")
    if len(inputs) < len(attempts):
        return {
            "input": sum(inputs),
            "output": sum(outputs),
            "source": "partial",
        }
    return {"input": sum(inputs), "output": sum(outputs), "source": "reported"}


def aggregate_cost(attempts: list[dict[str, Any]]) -> dict[str, Any]:
    if not attempts:
        return empty_cost()
    inputs: list[float] = []
    outputs: list[float] = []
    totals: list[float] = []
    reported = 0
    for a in attempts:
        c = normalize_cost(a.get("cost_usd"))
        if c["source"] == "unavailable":
            continue
        reported += 1
        if c["input"] is not None:
            inputs.append(float(c["input"]))
        if c["output"] is not None:
            outputs.append(float(c["output"]))
        if c["total"] is not None:
            totals.append(float(c["total"]))
    if reported == 0:
        return empty_cost("unavailable")
    src = "reported" if reported == len(attempts) else "partial"
    total = sum(totals) if totals else None
    if total is None and inputs and outputs and len(inputs) == len(outputs):
        total = sum(inputs) + sum(outputs)
    return {
        "input": sum(inputs) if inputs else None,
        "output": sum(outputs) if outputs else None,
        "total": total,
        "source": src,
    }


def read_alive_ids(path: Path) -> list[int]:
    if not path.exists():
        return []
    ids: list[int] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        ids.append(int(s))
    return ids


def write_alive_ids(path: Path, ids: list[int]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    text = "".join(f"{i}\n" for i in ids)
    fd, tmp_name = tempfile.mkstemp(
        dir=str(path.parent), prefix=f".{path.name}.", suffix=".tmp"
    )
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as fh:
            fh.write(text)
            fh.flush()
            os.fsync(fh.fileno())
        os.replace(tmp_name, path)
    except Exception:
        try:
            os.unlink(tmp_name)
        except OSError:
            pass
        raise


_STATUS_RE = re.compile(
    r"Status\s+(\w+)", re.IGNORECASE
)
_MUTANT_RE = re.compile(r"MUTANT\s*#\s*(\d+)", re.IGNORECASE)
_CAUSA_RE = re.compile(
    r"Causa\s+Mortis:\s*(.+?)\s*-\s*Test\s+Case\s+(-?\d+)",
    re.IGNORECASE,
)


def parse_muta_listing(text: str) -> dict[str, Any]:
    mutant_id = None
    life = "Unknown"
    active = None
    causa = None
    test_case = None
    for line in text.splitlines():
        m = _MUTANT_RE.search(line)
        if m:
            mutant_id = int(m.group(1))
            continue
        m = _STATUS_RE.search(line)
        if m:
            life = m.group(1)
            parts = line.strip().split()
            # e.g. Status Alive Active
            if len(parts) >= 3:
                active = parts[2]
            continue
        m = _CAUSA_RE.search(line)
        if m:
            causa = m.group(1).strip()
            test_case = int(m.group(2))
    return {
        "mutant_id": mutant_id,
        "life": life,
        "active": active,
        "causa_mortis": causa,
        "killing_test_case": test_case,
        "is_dead": life.lower() == "dead",
    }
