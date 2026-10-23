#!/usr/bin/env python3
"""Ask an LLM for a kill case given original + mutated sources; fill oracles."""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path
from typing import Any

sys.path.insert(0, str(Path(__file__).resolve().parent))
from inspect_mutant import inspect
from llm_client import chat_completion, completion_text, usage_tokens
from oracle_capture import ORACLE_COLS, capture_oracles

JSON_BLOCK_RE = re.compile(r"```(?:json)?\s*(\{.*?\})\s*```", re.S)


def _extract_json_object(text: str) -> dict[str, Any]:
    text = text.strip()
    m = JSON_BLOCK_RE.search(text)
    if m:
        text = m.group(1)
    else:
        start = text.find("{")
        end = text.rfind("}")
        if start >= 0 and end > start:
            text = text[start : end + 1]
    data = json.loads(text)
    if not isinstance(data, dict):
        raise ValueError("LLM JSON root must be an object")
    return data


def _original_source(program_dir: Path, function: str) -> str:
    # Prefer a .c file matching program name; fall back to first non-muta .c
    cands = sorted(program_dir.glob("*.c"))
    preferred = [
        p
        for p in cands
        if not p.name.startswith("muta")
        and not p.name.startswith("__")
        and "runner" not in p.name
    ]
    for path in preferred:
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if re.search(rf"\b{re.escape(function)}\s*\(", text):
            return text[:12000]
    if preferred:
        return preferred[0].read_text(encoding="utf-8", errors="replace")[:12000]
    return ""


def _mutant_source(program_dir: Path, session: str, mutant_id: int) -> str:
    for name in (f"muta{mutant_id}_{session}.c", f"muta{mutant_id}_{session}"):
        p = program_dir / name
        if p.exists():
            return p.read_text(encoding="utf-8", errors="replace")[:12000]
    return ""


def propose_kill_case(
    *,
    program_dir: Path,
    session: str,
    mutant_id: int,
    model: str,
    api_key: str,
    api_url: str,
    prior_failures: list[dict[str, Any]] | None = None,
) -> dict[str, Any]:
    insp = inspect(program_dir, session, mutant_id)
    if not insp.get("inspect_usable", True):
        raise RuntimeError(
            f"insufficient mutation context for mutant {mutant_id}: "
            f"{insp.get('inspect_error')}"
        )
    fn = insp.get("detected_function")
    if not fn:
        raise RuntimeError(f"no detected function for mutant {mutant_id}")
    schema = (insp.get("csv_schemas") or {}).get(fn) or {}
    if not schema.get("exists"):
        raise RuntimeError(f"no CSV schema for function {fn!r}")

    headers = list(schema.get("headers") or [])
    example = schema.get("format_example_row")
    get_on = insp.get("get_on") or ""
    op = insp.get("operator") or ""
    original = _original_source(program_dir, fn)
    mutated = _mutant_source(program_dir, session, mutant_id) or (
        insp.get("build_view") or ""
    )[:12000]

    prior = prior_failures or []
    system = (
        "You invent ONE CUnit CSV test case to kill a Proteum mutant. "
        "Reply with a single JSON object only (no markdown prose). "
        'Keys: "function" (string), "fields" (object of CSV column→string, '
        "omit test_number; oracle columns may be empty), "
        '"rationality" (string explaining how the input distinguishes the mutant).'
    )
    user = {
        "program": program_dir.name,
        "operator": op,
        "mutant_id": mutant_id,
        "function": fn,
        "csv_headers": headers,
        "format_example_row": example,
        "get_on": get_on,
        "original_source": original,
        "mutated_source": mutated,
        "prior_failed_fields": prior,
        "instructions": (
            "Choose inputs that reach Get on: and make original vs mutant "
            "differ on return value or stdout observed by the harness. "
            "Do not reuse prior_failed_fields."
        ),
    }
    resp = chat_completion(
        api_url=api_url,
        api_key=api_key,
        model=model,
        messages=[
            {"role": "system", "content": system},
            {"role": "user", "content": json.dumps(user, ensure_ascii=False)},
        ],
    )
    text = completion_text(resp)
    tokens = usage_tokens(resp)
    parsed = _extract_json_object(text)
    out_fn = str(parsed.get("function") or fn)
    fields = parsed.get("fields")
    if not isinstance(fields, dict):
        raise RuntimeError("LLM JSON missing fields object")
    # stringify values
    clean = {str(k): "" if v is None else str(v) for k, v in fields.items()}
    # drop test_number if present
    clean.pop("test_number", None)
    rationality = str(parsed.get("rationality") or "").strip()
    if not rationality:
        rationality = f"LLM case aimed at Get on: `{get_on}`"

    # Fill oracles from original
    filled = capture_oracles(program_dir, out_fn, headers, clean)
    capture_ok = bool(filled.pop("_capture_ok", True))
    filled.pop("_runner_exit", None)
    for col in ORACLE_COLS:
        if col in headers and col not in filled:
            filled[col] = ""

    return {
        "function": out_fn,
        "fields": filled,
        "rationality": rationality,
        "llm_name": model,
        "tokens": tokens,
        "capture_ok": capture_ok,
        "inspection": {
            "detected_function": fn,
            "get_on": get_on,
            "operator": op,
        },
    }


def propose_equivalence_rationality(
    *,
    program_dir: Path,
    session: str,
    mutant_id: int,
    model: str,
    api_key: str,
    api_url: str,
    prior_failures: list[dict[str, Any]],
) -> str:
    insp = inspect(program_dir, session, mutant_id)
    fn = insp.get("detected_function") or "unknown"
    get_on = insp.get("get_on") or ""
    op = insp.get("operator") or ""
    original = _original_source(program_dir, fn)
    mutated = _mutant_source(program_dir, session, mutant_id) or (
        insp.get("build_view") or ""
    )[:8000]
    system = (
        "You explain why a Proteum mutant may be a possible equivalent under "
        "the CUnit CSV interface. Write 4–8 sentences covering: what changed "
        "(Get on:), why observable behaviour may match, what was tried, and "
        "residual doubt. Do NOT say only that it survived N attempts."
    )
    user = {
        "program": program_dir.name,
        "operator": op,
        "mutant_id": mutant_id,
        "function": fn,
        "get_on": get_on,
        "original_source": original[:6000],
        "mutated_source": mutated[:6000],
        "failed_attempts": prior_failures,
    }
    resp = chat_completion(
        api_url=api_url,
        api_key=api_key,
        model=model,
        messages=[
            {"role": "system", "content": system},
            {"role": "user", "content": json.dumps(user, ensure_ascii=False)},
        ],
    )
    return completion_text(resp).strip()
