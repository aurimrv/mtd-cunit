#!/usr/bin/env python3
"""
Mutation-oriented input generation for CUnit CSV cases (not ts_data row reuse).

Deterministic / heuristic synthesizer — does NOT call an LLM. Uses inspect_mutant
for Get on: / schema encoding, synthesizes distinct input rows aimed at the
current mutant, then fills expected_output / expected_stdout via CUNIT_CAPTURE=1
against the original ./runner.

SSDL (statement deletion) gets build-view–aware targeting: the deleted @…@
fragment and surrounding control-flow drive inputs so the removed statement is
likely reached (SSDL equivalents are rare; weak probes must not dominate).
"""

from __future__ import annotations

import argparse
import csv
import json
import os
import re
import subprocess
import tempfile
from pathlib import Path
from typing import Any

from inspect_mutant import inspect

INT_RE = re.compile(r"-?\d+")
OBS_RE = re.compile(r"CMAGUT_OBS\s+(\{.*\})")
ORACLE_COLS = ("expected_output", "expected_stdout")
STR_LIT_RE = re.compile(r"'([^'\\]|\\.)'|\"([^\"\\]|\\.)\"")
IDENT_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\b")


def _encode_csv_oracle(value: str) -> str:
    """
    CUnit CSV loaders are line-oriented and decode \\n/\\r/\\t escapes.
    Store oracles with those escapes (never raw newlines) so any C program
    harness can round-trip stdout/output oracles.
    """
    if value is None:
        return ""
    s = str(value).replace("\x00", "")
    return (
        s.replace("\\", "\\\\")
        .replace("\n", "\\n")
        .replace("\r", "\\r")
        .replace("\t", "\\t")
    )


def _sanitize_fields(fields: dict[str, str]) -> dict[str, str]:
    """Strip NULs so argv/env handoff to run_attempt never raises."""
    out: dict[str, str] = {}
    for k, v in fields.items():
        out[str(k).replace("\x00", "")] = (
            "" if v is None else str(v).replace("\x00", "")
        )
    return out


def _nums(text: str) -> list[int]:
    out: list[int] = []
    for m in INT_RE.finditer(text or ""):
        try:
            out.append(int(m.group(0)))
        except ValueError:
            continue
    return out


def _is_int_list_cell(raw: str) -> bool:
    """True only for non-empty comma-separated integers (not bare ',')."""
    parts = [p.strip() for p in raw.split(",")]
    if not parts or all(p == "" for p in parts):
        return False
    return all(p.lstrip("-").isdigit() for p in parts if p)


_STRING_FIELD_NAMES = frozenset(
    {
        "s",
        "str",
        "string",
        "text",
        "line",
        "input",
        "arg",
        "pat",
        "sub",
        "lin",
        "token_str",
        "buf",
        "buffer",
        "outset",
        "name",
        "word",
        "msg",
        "message",
    }
)
_SIZEISH_FIELD_NAMES = frozenset(
    {
        "n",
        "size",
        "len",
        "length",
        "max",
        "maxset",
        "maxsize",
        "maxlen",
        "capacity",
        "count",
        "k",
        "num",
        "ncols",
        "nrows",
    }
)
# Discriminating string probes (palindrome / mismatch / empty edge) — not program-specific
_STRING_PROBES = (
    "a",
    "ab",
    "aba",
    "abba",
    "abc",
    "Aa",
    "racecar",
    "x",
    "",
    "abca",
)


def _perturb_scalar(
    value: str,
    seed: int,
    get_nums: list[int],
    *,
    field_name: str = "",
) -> str:
    raw = (value or "").strip()
    fname = (field_name or "").lower()
    # Empty string columns must not stay empty for SSDL reachability (except as one probe)
    if raw in ("NULL", "NONNULL"):
        return raw
    if raw == "":
        if fname in _STRING_FIELD_NAMES or fname in {"c", "ch"}:
            return _STRING_PROBES[seed % len(_STRING_PROBES)]
        if fname in _SIZEISH_FIELD_NAMES or fname in {"n", "N"} or fname.isupper():
            return str([1, 2, 3, 5, 10, 0, 4, 7][seed % 8])
        return "1"
    # Single-char delimiters / punctuation — never treat as int-lists
    if fname in {"delim", "c", "ch"} or (len(raw) == 1 and not raw.isdigit()):
        if fname == "delim":
            return [",", ";", "|", ":", "/"][seed % 5]
        if fname in {"c", "ch"}:
            return ["A", "B", "a", "*", "%", "$", "?"][seed % 7]
        # Single-char string field: expand to discriminating probes
        if fname in _STRING_FIELD_NAMES:
            return _STRING_PROBES[seed % len(_STRING_PROBES)]
        return raw
    # comma-separated int list (non-empty cells only)
    if "," in raw and _is_int_list_cell(raw):
        parts = [int(p.strip()) for p in raw.split(",") if p.strip()]
        if not parts:
            parts = [seed, seed + 1, seed + 2]
        shift = (seed % 7) - 3
        parts = [p + shift for p in parts]
        if get_nums:
            parts[0] = get_nums[seed % len(get_nums)]
        return ",".join(str(p) for p in parts)
    # queue encoding: cap=N|init=...
    if "cap=" in raw and "|" in raw:
        m = re.search(r"cap=(-?\d+)", raw)
        cap = int(m.group(1)) if m else 3
        caps = [max(1, cap + d) for d in (-2, -1, 0, 1, 2, 3)]
        new_cap = caps[seed % len(caps)]
        init_m = re.search(r"init=([^|]*)", raw)
        init = init_m.group(1) if init_m else ""
        if seed % 3 == 0:
            init = ""
        elif seed % 3 == 1:
            vals = get_nums[:new_cap] if get_nums else list(range(seed, seed + min(new_cap, 3)))
            init = ",".join(str(v) for v in vals[:new_cap])
        else:
            vals = [10 + seed, 20 + seed, 30 + seed][: min(new_cap, 3)]
            init = ",".join(str(v) for v in vals)
        return f"cap={new_cap}|init={init}"
    # plain int / float-like numeric string
    if raw.lstrip("-").replace(".", "", 1).isdigit() and raw.count(".") <= 1:
        try:
            n = float(raw) if "." in raw else int(raw)
        except ValueError:
            n = 1
        if isinstance(n, float) or fname in {"sigma", "z", "mu", "x", "y"}:
            pool_f = [n - 2, n - 1, n, n + 1, n + 2, 0.5, 1.0, 2.0, -1.0, 0.1]
            if fname == "sigma":
                pool_f = [x for x in pool_f if x != 0] or [1.0, 0.5, 2.0]
            return str(pool_f[seed % len(pool_f)])
        n_i = int(n)
        # Size / count / N: prefer non-negative (negatives often crash harnesses)
        if fname in _SIZEISH_FIELD_NAMES or fname in {"n", "N"} or (
            len(fname) <= 2 and fname.isupper()
        ):
            base = abs(n_i) if n_i != 0 else 1
            # Include multi-digit values so digit/modulo loops run >1 iteration
            pool = [
                base,
                base + 1,
                base + 2,
                max(0, base - 1),
                0,
                1,
                2,
                5,
                10,
                12,
                21,
                100,
                123,
                4567,
            ]
        else:
            pool = [n_i - 2, n_i - 1, n_i, n_i + 1, n_i + 2, 0, 1, -1, 2, 5, 10]
        pool.extend(x for x in get_nums if x >= 0 or fname not in _SIZEISH_FIELD_NAMES)
        if fname == "sigma":
            pool = [x for x in pool if x != 0]
        seen: set[int] = set()
        ordered: list[int] = []
        for x in pool:
            if x not in seen:
                seen.add(x)
                ordered.append(x)
        return str(ordered[seed % len(ordered)])
    # format-string-like argv
    if "%" in raw and fname == "argv":
        variants = [
            raw,
            "%",
            "%H:%M %h %d",
            "%T",
            "abc%n%txyz",
            "%d/%m/%y",
            "x%Sy",
            "%q",
        ]
        return variants[seed % len(variants)]
    # Harness stdin tokens — only when the seeded value already uses them
    if raw in {"push", "eof"}:
        return ["push", "eof"][seed % 2]
    # Generic string fields: discriminating probes (do NOT force push/eof)
    if fname in _STRING_FIELD_NAMES:
        probes = list(_STRING_PROBES)
        if raw and raw not in probes:
            probes = [raw, f"{raw}_m{seed}", raw + "a", "a" + raw] + probes
        return probes[seed % len(probes)]
    if seed == 0:
        return raw
    return f"{raw}_m{seed}" if len(raw) < 40 else raw


def _sync_argc_argv(fields: dict[str, str]) -> None:
    if "argc" not in fields or "argv" not in fields:
        return
    argv = fields.get("argv") or ""
    n_tok = len(argv.split(",")) if argv != "" else 0
    try:
        argc = int(str(fields["argc"]).strip())
    except ValueError:
        fields["argc"] = str(n_tok)
        return
    if argc > n_tok:
        fields["argc"] = str(n_tok)


def _extract_ssdl_context(build_view: str) -> dict[str, Any]:
    """Parse Proteum build-view @deleted@ region and nearby source."""
    view = build_view or ""
    m = re.search(r"@([^@]*)@", view, re.S)
    deleted = (m.group(1).strip() if m else "")
    at = view.find("@")
    before = view[max(0, at - 250) : at] if at >= 0 else view[:250]
    after = view[at : at + 250] if at >= 0 else ""
    context = before + deleted + after

    def _lits_in(text: str) -> list[str]:
        out: list[str] = []
        for sm in STR_LIT_RE.finditer(text or ""):
            lit = sm.group(0)[1:-1]
            if lit and lit not in out:
                out.append(lit)
        return out

    deleted_lits = _lits_in(deleted)
    # Prefer deleted-only lits for targeting; context lits are fallback only
    context_lits = [x for x in _lits_in(context) if x not in deleted_lits]
    lits = deleted_lits + context_lits
    idents = [
        x
        for x in IDENT_RE.findall(deleted)
        if x
        not in {
            "if",
            "else",
            "while",
            "for",
            "return",
            "bool",
            "int",
            "char",
            "void",
            "true",
            "false",
            "NULL",
        }
    ]
    return {
        "deleted": deleted,
        "before": before,
        "after": after,
        "context": context,
        "string_lits": lits,
        "deleted_lits": deleted_lits,
        "idents": idents,
    }


def _schema_has(headers: list[str], *names: str) -> bool:
    lower = {h.lower() for h in headers}
    return all(n.lower() in lower for n in names)


def _header_named(headers: list[str], *candidates: str) -> str | None:
    lower_map = {h.lower(): h for h in headers}
    for c in candidates:
        if c.lower() in lower_map:
            return lower_map[c.lower()]
    return None


def _pattern_arg_ssdl_fields(ctx: dict[str, Any], iteration: int) -> dict[str, str]:
    """
    Schema-agnostic probes for functions that parse a delimited pattern/arg string.

    Driven by char/string literals in the *deleted* statement first. When the
    deleted fragment has no literals (e.g. a helper call), use a covering
    alphabet so alternate branches are still exercised — program-agnostic.
    """
    deleted_lits = [x for x in (ctx.get("deleted_lits") or []) if x]
    all_lits = [x for x in (ctx.get("string_lits") or []) if x]
    primary: list[str] = []
    for lit in deleted_lits:
        if len(lit) == 1:
            primary += [lit, f"a{lit}", f"{lit}a", f"{lit}*"]
        else:
            primary.append(lit[:12])
    # Generic covering set for scanner-style parsers (not program-specific names)
    cover = ["a*", "?*", "[a]", "a", "ab", "?", "%", "$", "*", "@a", "^a$", "%a"]
    # No deleted literals / call-only deletion → covering set leads (reach branches)
    if not deleted_lits:
        pool = cover + [p for p in primary if p not in cover]
    else:
        pool = primary + [p for p in cover if p not in primary]
    if not pool:
        pool = cover
    arg_body = pool[(iteration - 1) % len(pool)]
    delim = ","
    for lit in deleted_lits + all_lits:
        if len(lit) == 1 and lit in ",;|:/\t":
            delim = lit
            break
    arg = arg_body if arg_body.endswith(delim) else arg_body + delim
    return {"arg": arg, "start": "0", "delim": delim, "pat": "x"}


def _indexed_buffer_ssdl_fields(
    headers: list[str], ctx: dict[str, Any], iteration: int
) -> dict[str, str]:
    """
    Schema-agnostic probes for append/write helpers with (char, buffer, index, max).

    Hits both full-buffer and in-bounds write paths so SSDL of either the
    failure assign or the buffer side effects can be distinguished when the
    harness oracle observes buffer/index (not only the return value).
    """
    deleted = (ctx.get("deleted") or "").lower()
    if "result" in deleted and any(
        x in deleted for x in ("false", "result = 0", "result=0", "= 0", "=0")
    ):
        pairs = [(3, 3), (5, 3), (0, 0), (1, 1), (10, 10), (4, 4), (2, 2), (7, 7)]
    elif "result" in deleted and any(
        x in deleted for x in ("true", "result = 1", "result=1", "= 1", "=1")
    ):
        pairs = [(0, 3), (1, 5), (2, 4), (0, 1), (3, 8), (1, 2), (4, 9), (5, 10)]
    else:
        # Side-effect deletions (store / index bump): prefer in-bounds writes
        pairs = [(0, 3), (1, 3), (2, 3), (0, 1), (4, 8), (1, 2), (3, 3), (5, 5)]
    j, mx = pairs[(iteration - 1) % len(pairs)]
    lits = ctx.get("string_lits") or []
    ch = (lits[(iteration - 1) % len(lits)][:1] if lits else None) or [
        "A",
        "B",
        "*",
        "%",
        "$",
        "?",
        "x",
        "0",
    ][(iteration - 1) % 8]
    c_h = _header_named(headers, "c", "ch", "char", "character")
    buf_h = _header_named(headers, "outset", "buf", "buffer", "s", "dest", "out")
    j_h = _header_named(headers, "j", "i", "index", "pos", "offset")
    max_h = _header_named(headers, "maxset", "max", "maxsize", "maxlen", "capacity", "n")
    fields: dict[str, str] = {}
    if c_h:
        fields[c_h] = ch
    if buf_h:
        fields[buf_h] = f"buf_{iteration}"
    if j_h:
        fields[j_h] = str(j)
    if max_h:
        fields[max_h] = str(mx)
    return fields


def _stdin_token_ssdl_fields(
    headers: list[str],
    format_example: dict[str, str] | None,
    get_on: str,
    iteration: int,
) -> dict[str, str]:
    """When CSV has an `s` (or line) column whose examples are harness tokens."""
    fields = _synthesize_inputs(headers, format_example, get_on, iteration)
    s_h = _header_named(headers, "s", "line", "input", "stdin")
    if not s_h:
        return fields
    example = ""
    if format_example and s_h in format_example:
        example = str(format_example[s_h] or "")
    # Only use push/eof vocabulary when the seeded harness already uses it
    if example.lower() in {"push", "eof"} or "push" in example.lower():
        fields[s_h] = ["push", "eof", "push", "eof", "push"][(iteration - 1) % 5]
    return fields


def _generic_ssdl_fields(
    headers: list[str],
    format_example: dict[str, str] | None,
    ctx: dict[str, Any],
    iteration: int,
) -> dict[str, str]:
    """Inject deleted-statement literals into matching CSV columns."""
    fields: dict[str, str] = {}
    lits = ctx.get("string_lits") or []
    get_nums = _nums(ctx.get("deleted") or "")
    str_cols = {
        "arg",
        "pat",
        "sub",
        "lin",
        "s",
        "line",
        "token_str",
        "outset",
        "buf",
        "buffer",
        "c",
        "ch",
        "delim",
        "input",
        "str",
        "text",
    }
    for h in headers:
        if h in ORACLE_COLS or h == "test_number":
            continue
        base = ""
        if format_example and h in format_example and format_example[h] is not None:
            base = str(format_example[h])
        # Prefer placing a literal into string-ish columns
        if lits and h.lower() in str_cols:
            lit = lits[(iteration - 1) % len(lits)]
            if h.lower() == "delim" and len(lit) == 1:
                fields[h] = lit
            elif h.lower() in {"c", "ch"} and lit:
                fields[h] = lit[0]
            elif h.lower() in str_cols - {"delim", "c", "ch"}:
                fields[h] = f"{lit}a" if len(lit) == 1 else lit
            else:
                fields[h] = _perturb_scalar(base or "1", iteration - 1, get_nums, field_name=h)
        else:
            fields[h] = _perturb_scalar(
                base or ("1" if h not in ("q", "queue") else "cap=3|init="),
                iteration - 1,
                get_nums,
                field_name=h,
            )
    _sync_argc_argv(fields)
    return fields


def _synthesize_inputs(
    headers: list[str],
    format_example: dict[str, str] | None,
    get_on: str,
    iteration: int,
) -> dict[str, str]:
    get_nums = _nums(get_on)
    fields: dict[str, str] = {}
    for h in headers:
        if h in ORACLE_COLS or h == "test_number":
            continue
        base = ""
        if format_example and h in format_example and format_example[h] is not None:
            base = str(format_example[h])
        elif h in ("q", "queue"):
            base = "cap=3|init="
        elif h in ("x", "arr", "a", "values"):
            base = "1,2,3"
        elif h in ("size", "n", "len", "maxElements", "capacity"):
            base = "3"
        elif h == "delim":
            base = ","
        else:
            base = "1"
        fields[h] = _perturb_scalar(base, iteration - 1, get_nums, field_name=h)
    for h in fields:
        if h not in ORACLE_COLS and fields[h] == (format_example or {}).get(h, None):
            fields[h] = _perturb_scalar(fields[h], iteration + 3, get_nums, field_name=h)
            break
    _sync_argc_argv(fields)
    if "sigma" in fields:
        try:
            if float(fields["sigma"]) == 0.0:
                fields["sigma"] = "1"
        except ValueError:
            fields["sigma"] = "1"
    return fields


def _synthesize_inputs_for_mutant(
    headers: list[str],
    format_example: dict[str, str] | None,
    insp: dict[str, Any],
    iteration: int,
) -> dict[str, str]:
    op = (insp.get("operator") or "").lower()
    fn = insp.get("detected_function") or ""
    get_on = insp.get("get_on") or ""
    view = insp.get("build_view") or ""
    is_ssdl = "ssdl" in op or op.endswith("u-ssdl")

    if is_ssdl:
        ctx = _extract_ssdl_context(view)
        # Schema-driven (program-agnostic) SSDL targeting — never match on fn name.
        if _schema_has(headers, "arg", "delim") and (
            _header_named(headers, "pat", "pattern") or _header_named(headers, "start")
        ):
            base = _pattern_arg_ssdl_fields(ctx, iteration)
            fields = {
                k: v
                for k, v in base.items()
                if k in headers or k.lower() in {h.lower() for h in headers}
            }
        elif _header_named(headers, "arg") and not _header_named(headers, "delim"):
            mp = _pattern_arg_ssdl_fields(ctx, iteration)
            fields = _generic_ssdl_fields(headers, format_example, ctx, iteration)
            ah = _header_named(headers, "arg")
            if ah:
                fields[ah] = mp["arg"].rstrip(",;")
            ph = _header_named(headers, "pat", "pattern")
            if ph:
                fields[ph] = mp.get("pat", "x")
        elif _header_named(headers, "c", "ch", "char") and _header_named(
            headers, "j", "i", "index"
        ) and _header_named(headers, "maxset", "max", "maxsize", "maxlen", "capacity"):
            fields = _generic_ssdl_fields(headers, format_example, ctx, iteration)
            fields.update(_indexed_buffer_ssdl_fields(headers, ctx, iteration))
        elif _header_named(headers, "s", "line", "input", "stdin"):
            fields = _stdin_token_ssdl_fields(headers, format_example, get_on, iteration)
        else:
            fields = _generic_ssdl_fields(headers, format_example, ctx, iteration)
        fields = _boost_numeric_for_deleted(fields, ctx, iteration)
        return _boost_schema_reachability(fields, headers, ctx, iteration)
    return _synthesize_inputs(headers, format_example, get_on, iteration)


def _boost_numeric_for_deleted(
    fields: dict[str, str], ctx: dict[str, Any], iteration: int
) -> dict[str, str]:
    """If deleted stmt does digit/modulo work, prefer multi-digit ints (any program)."""
    deleted = (ctx.get("deleted") or "").lower()
    if not any(tok in deleted for tok in ("% 10", "%10", "/ 10", "/10", "digit", "%")):
        return fields
    multi = [10, 12, 21, 100, 123, 4567, 98, 76]
    for h, v in list(fields.items()):
        hl = h.lower()
        if hl in ORACLE_COLS or h == "test_number":
            continue
        if hl in _SIZEISH_FIELD_NAMES or hl in {"n"} or (len(h) <= 2 and h.isupper()):
            # Only rewrite plain ints
            if str(v).lstrip("-").isdigit():
                fields[h] = str(multi[(iteration - 1) % len(multi)])
    return fields


_ARRAYISH_HEADERS = frozenset(
    {
        "list",
        "arr",
        "a",
        "pq",
        "src",
        "dest",
        "temp",
        "values",
        "items",
        "x",
        "vec",
        "nums",
        "data",
    }
)
_RANGE_LO_CANDS = ("low", "lo", "start", "begin", "from", "left")
_RANGE_HI_CANDS = ("high", "hi", "end", "finish", "to", "right")


def _parse_intish(raw: str) -> int | None:
    s = str(raw or "").strip()
    if s.lstrip("-").isdigit():
        try:
            return int(s)
        except ValueError:
            return None
    return None


def _unsorted_int_list(n: int, seed: int) -> str:
    """Comma-separated ints of length n that are not already sorted ascending."""
    n = max(2, n)
    base = [((seed + 3) * (i + 3) + 7) % 97 for i in range(n)]
    # Guarantee not sorted / not identity 0..n-1
    if base == sorted(base):
        base[-1], base[0] = base[0], base[-1]
    if base == list(range(n)):
        base[0], base[-1] = base[-1], base[0]
    return ",".join(str(x) for x in base)


def _unsorted_token_list(n: int, seed: int) -> str:
    n = max(2, n)
    alphabet = "zyxwvutsrqponmlkjihgfedcba"
    toks = [alphabet[(seed + i * 3) % len(alphabet)] for i in range(n)]
    if toks == sorted(toks):
        toks[0], toks[-1] = toks[-1], toks[0]
    return ",".join(toks)


def _boost_schema_reachability(
    fields: dict[str, str],
    headers: list[str],
    ctx: dict[str, Any],
    iteration: int,
) -> dict[str, str]:
    """
    Schema-driven reachability boosts (header names + deleted tokens only).

    - Range pairs: force lo < hi with span >= 1 on most probes.
    - Length/N with an array column: prefer length >= 2 and unsorted contents.
    - Deleted stmt writes indexed containers: bias non-empty containers.
    - Size-only / stdout-style drivers: prefer n >= 2.
    """
    deleted = ctx.get("deleted") or ""
    seed = max(0, iteration - 1)

    # 1) Range pairs (low/high, start/end, i/j)
    lo_h = _header_named(headers, *_RANGE_LO_CANDS)
    hi_h = _header_named(headers, *_RANGE_HI_CANDS)
    if lo_h and hi_h and lo_h in fields and hi_h in fields:
        lo = _parse_intish(fields[lo_h])
        hi = _parse_intish(fields[hi_h])
        if lo is None:
            lo = 0
        if hi is None or hi <= lo:
            # Most probes: span at least 1; rare equal-bound probe for edges
            if seed % 7 == 0:
                fields[lo_h] = str(lo)
                fields[hi_h] = str(lo)
            else:
                span = 1 + (seed % 4)
                fields[lo_h] = str(lo)
                fields[hi_h] = str(lo + span)
    ij_i = _header_named(headers, "i")
    ij_j = _header_named(headers, "j")
    if (
        ij_i
        and ij_j
        and ij_i in fields
        and ij_j in fields
        and not (lo_h == ij_i and hi_h == ij_j)
    ):
        i_v = _parse_intish(fields[ij_i])
        j_v = _parse_intish(fields[ij_j])
        if i_v is None:
            i_v = 0
        if j_v is None or j_v == i_v:
            if seed % 7 != 0:
                fields[ij_i] = str(i_v)
                fields[ij_j] = str(i_v + 1 + (seed % 3))

    # 2) Length / N paired with an array-ish column
    arr_h = next(
        (
            h
            for h in headers
            if h.lower() in _ARRAYISH_HEADERS and h in fields
        ),
        None,
    )
    len_h = _header_named(
        headers, "len", "length", "n", "N", "size", "count", "num"
    )
    if arr_h and len_h and len_h in fields:
        n_v = _parse_intish(fields[len_h])
        if n_v is None or n_v < 2:
            n_v = 2 + (seed % 4)
            fields[len_h] = str(n_v)
        raw = str(fields.get(arr_h) or "")
        parts = [p for p in raw.split(",") if p != ""]
        if len(parts) < 2 or parts == sorted(parts) or (
            all(p.lstrip("-").isdigit() for p in parts)
            and [int(p) for p in parts] == list(range(len(parts)))
        ):
            if all(p.lstrip("-").isdigit() for p in parts) or not parts:
                fields[arr_h] = _unsorted_int_list(n_v, seed)
            else:
                fields[arr_h] = _unsorted_token_list(n_v, seed)

    # 3) Deleted stmt writes indexed containers → non-empty destination
    if any(tok in deleted for tok in ("[", "->", "strcpy", "memcpy", "strncpy")):
        for h in list(fields):
            hl = h.lower()
            if hl in ORACLE_COLS or h == "test_number":
                continue
            if hl in _ARRAYISH_HEADERS or hl in {
                "outset",
                "buf",
                "buffer",
                "dest",
                "pat",
            }:
                if str(fields[h]).strip() in {"", "0", "NULL"}:
                    if hl in _ARRAYISH_HEADERS:
                        fields[h] = _unsorted_int_list(3, seed)
                    else:
                        fields[h] = f"ab{(seed % 9)}"

    # 4) Size-only drivers (often stdout): prefer n >= 2
    input_headers = [
        h
        for h in headers
        if h not in ORACLE_COLS and h != "test_number" and h in fields
    ]
    size_only = input_headers and all(
        h.lower() in _SIZEISH_FIELD_NAMES or h.lower() in {"n", "n"}
        for h in input_headers
    )
    if size_only:
        for h in input_headers:
            v = _parse_intish(fields[h])
            if v is not None and v < 2 and seed % 5 != 0:
                fields[h] = str(2 + (seed % 5))

    # 5) ADT scenario depth: prefer n_jobs >= 2 on most probes
    nj_h = _header_named(headers, "n_jobs", "njobs", "num_jobs")
    if nj_h and nj_h in fields:
        nj = _parse_intish(fields[nj_h])
        if nj is None or nj < 2:
            if seed % 6 != 0:
                fields[nj_h] = str(2 + (seed % 3))

    return fields


def _capture_oracles(
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
            result[col] = _encode_csv_oracle(val if val is not None else "")
        result["_capture_ok"] = bool(captured) or not oracle_headers
        result["_runner_exit"] = cp.returncode
        return result


def _equivalence_rationality(insp: dict[str, Any], n_attempts: int) -> str:
    get_on = (insp.get("get_on") or "").strip() or "(unavailable)"
    fn = insp.get("detected_function") or "unknown"
    op = insp.get("operator") or "unknown"
    view = (insp.get("build_view") or "")[:400]
    ctx = _extract_ssdl_context(insp.get("build_view") or "")
    deleted = ctx.get("deleted") or ""

    if "ssdl" in op.lower():
        dlow = deleted.lower()
        if "result" in dlow and any(
            x in dlow
            for x in ("false", "true", "result = 0", "result = 1", "result=0", "result=1")
        ):
            hyp = (
                "SSDL deleted only a bool/int result assign with no other side effect; "
                "under gcc this often matches the original return (uninit→0) — a rare "
                f"observational equivalent for return-only harnesses. Deleted: {deleted!r}."
            )
        else:
            hyp = (
                "true SSDL equivalents are rare; Alive usually means the harness did not "
                "observe the deleted effect (e.g. return-only oracle missing pat[]/buffers) "
                "or the site was unreached — strengthen oracles before assuming equivalence. "
                f"Deleted: {deleted!r}."
            )
    else:
        hyp = (
            "the rewritten expression may preserve return value and stdout for inputs "
            "expressible through this function's CSV harness"
        )
        g = get_on.lower()
        if "=(" in get_on and get_on.count("=") >= 2:
            hyp = (
                "identity/self-assignment or deleted side-effect; may agree if the site "
                "is unreached or unasserted by this harness"
            )
        elif any(tok in get_on for tok in ("<", ">", "<=", ">=", "==", "!=")):
            hyp = (
                "relational/logical change may agree on the CSV-expressible input subset"
            )
        elif any(tok in g for tok in ("++", "--", "+ 1", "- 1")):
            hyp = "±1 rewrite may be invisible if the counter is unused by oracles"
        elif "!" in get_on or "OCNG" in op or "OLNG" in op:
            hyp = "negation/guard rewrite may agree if both branches look identical here"
        elif any(c.isdigit() for c in get_on):
            hyp = "constant rewrite may be dominated for this harness's value domain"

    return (
        f"Get on: `{get_on}`. Operator `{op}` in function `{fn}`. "
        f"Semantic hypothesis: {hyp}. "
        f"Build-view fragment (truncated): {view!r}. "
        f"After {n_attempts} mutation-directed probes (SSDL-aware when applicable) "
        f"with oracle = original runner (CUNIT_CAPTURE), the mutant remained Alive. "
        f"Residual doubt: stronger multi-call scenarios or encodings outside this CSV "
        f"schema might still kill it; mark as possible equivalent only under the "
        f"current interface and generation budget."
    )


def generate_for_mutant(
    program_dir: Path,
    session: str,
    mutant_id: int,
    max_candidates: int = 5,
) -> dict[str, Any]:
    insp = inspect(program_dir, session, mutant_id)
    if not insp.get("inspect_usable", True):
        err = insp.get("inspect_error") or "missing_build_view"
        raise RuntimeError(
            f"insufficient mutation context for mutant {mutant_id} ({err}); "
            f"refusing probes / EQUIVALENT (fail-closed)"
        )
    fn = insp.get("detected_function")
    if not fn:
        raise RuntimeError(f"no detected function for mutant {mutant_id}")
    schema = (insp.get("csv_schemas") or {}).get(fn) or {}
    if not schema.get("exists"):
        # Do not silently bind a different function's CSV (false probes).
        raise RuntimeError(
            f"no CSV schema for owning function {fn!r} (mutant {mutant_id}); "
            f"refusing cross-function fallback"
        )

    headers = list(schema.get("headers") or [])
    example = schema.get("format_example_row")
    get_on = insp.get("get_on") or ""
    op = insp.get("operator") or ""
    is_ssdl = "ssdl" in op.lower()
    # Give SSDL more distinct branch-hitting attempts by default
    n_cand = max(max_candidates, 8) if is_ssdl else max_candidates

    candidates: list[dict[str, Any]] = []
    seen_inputs: set[str] = set()
    ctx = _extract_ssdl_context(insp.get("build_view") or "") if is_ssdl else {}
    for i in range(1, n_cand + 1):
        inputs = _synthesize_inputs_for_mutant(headers, example, insp, i)
        key = json.dumps(inputs, sort_keys=True)
        nudge = 0
        while key in seen_inputs and nudge < 8:
            nudge += 1
            inputs = _synthesize_inputs_for_mutant(headers, example, insp, i + nudge * 11)
            key = json.dumps(inputs, sort_keys=True)
        seen_inputs.add(key)

        filled = _capture_oracles(program_dir, fn, headers, inputs)
        capture_ok = bool(filled.pop("_capture_ok", True))
        filled.pop("_runner_exit", None)
        filled = _sanitize_fields(filled)
        deleted = (ctx.get("deleted") or "")[:80].replace("\x00", "")
        rationality = (
            f"Mutation-oriented input generation for Get on: `{get_on}` "
            f"(operator `{op}`). Chose function `{fn}` from build-view. "
            f"Iteration {i}: synthesized NEW inputs { {k: v for k, v in inputs.items()} } "
            f"(not a ts_data row); oracles via CUNIT_CAPTURE (capture_ok={capture_ok}). "
            + (
                f"SSDL target deleted `{deleted}` — inputs chosen to reach that statement."
                if is_ssdl
                else "Targets the mutated expression via Get on: / nearby literals."
            )
        ).replace("\x00", "")
        candidates.append(
            {
                "mutant_id": mutant_id,
                "iteration": i,
                "function": fn,
                "fields": filled,
                "rationality": rationality,
                "_capture_ok": capture_ok,
            }
        )

    # Prefer candidates whose oracle capture succeeded (failed captures waste iterations)
    candidates.sort(key=lambda c: (0 if c.get("_capture_ok") else 1))
    for c in candidates:
        c.pop("_capture_ok", None)

    n_keep = max(max_candidates, 8) if is_ssdl else max_candidates
    kept = candidates[:n_keep]
    return {
        "mutant_id": mutant_id,
        "inspection": {
            "detected_function": fn,
            "get_on": get_on,
            "operator": op,
            "ssdl_deleted": ctx.get("deleted") if is_ssdl else None,
        },
        "candidates": kept,
        "equivalence_rationality": _equivalence_rationality(insp, len(kept)),
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--program-dir", required=True)
    p.add_argument("--session", required=True)
    p.add_argument("--mutant-id", type=int, required=True)
    p.add_argument("--max-candidates", type=int, default=5)
    p.add_argument("--jsonl-out", default=None, help="Append candidate lines here")
    args = p.parse_args()

    program_dir = Path(args.program_dir).resolve()
    if not (program_dir / "runner").exists():
        print("error: ./runner missing; compile first", flush=True)
        return 1

    bundle = generate_for_mutant(
        program_dir, args.session, args.mutant_id, args.max_candidates
    )
    if args.jsonl_out:
        out = Path(args.jsonl_out)
        out.parent.mkdir(parents=True, exist_ok=True)
        with out.open("a", encoding="utf-8") as fh:
            for cand in bundle["candidates"]:
                fh.write(json.dumps(cand) + "\n")
            fh.write(
                json.dumps(
                    {
                        "mutant_id": bundle["mutant_id"],
                        "equivalence_rationality": bundle["equivalence_rationality"],
                    }
                )
                + "\n"
            )
    print(json.dumps(bundle, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
