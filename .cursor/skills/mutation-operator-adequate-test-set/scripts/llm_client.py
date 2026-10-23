#!/usr/bin/env python3
"""Minimal OpenAI-compatible chat completions client (API_URLS + API_KEYS)."""

from __future__ import annotations

import json
import urllib.error
import urllib.request
from typing import Any


def chat_completion(
    *,
    api_url: str,
    api_key: str,
    model: str,
    messages: list[dict[str, str]],
    temperature: float = 0.2,
    timeout_s: float = 120.0,
) -> dict[str, Any]:
    """
    POST {api_url}/chat/completions (api_url may already end with /v1).
    Returns parsed JSON; raises RuntimeError on HTTP/parse failure.
    """
    base = api_url.rstrip("/")
    if base.endswith("/chat/completions"):
        url = base
    else:
        url = f"{base}/chat/completions"

    body = {
        "model": model,
        "messages": messages,
        "temperature": temperature,
    }
    data = json.dumps(body).encode("utf-8")
    req = urllib.request.Request(
        url,
        data=data,
        method="POST",
        headers={
            "Content-Type": "application/json",
            "Authorization": f"Bearer {api_key}",
        },
    )
    try:
        with urllib.request.urlopen(req, timeout=timeout_s) as resp:
            raw = resp.read().decode("utf-8", errors="replace")
    except urllib.error.HTTPError as exc:
        err_body = exc.read().decode("utf-8", errors="replace")[:800]
        raise RuntimeError(f"LLM HTTP {exc.code} from {url}: {err_body}") from exc
    except urllib.error.URLError as exc:
        raise RuntimeError(f"LLM request failed for {url}: {exc}") from exc

    try:
        parsed = json.loads(raw)
    except json.JSONDecodeError as exc:
        raise RuntimeError(f"LLM returned non-JSON: {raw[:400]}") from exc
    return parsed


def completion_text(response: dict[str, Any]) -> str:
    choices = response.get("choices") or []
    if not choices:
        raise RuntimeError(f"LLM response missing choices: {response!r}"[:500])
    msg = choices[0].get("message") or {}
    content = msg.get("content")
    if not isinstance(content, str) or not content.strip():
        raise RuntimeError("LLM response missing message.content")
    return content


def usage_tokens(response: dict[str, Any]) -> dict[str, Any]:
    usage = response.get("usage") or {}
    inp = usage.get("prompt_tokens")
    out = usage.get("completion_tokens")
    if inp is None and out is None:
        return {"input": None, "output": None, "source": "unavailable"}
    return {
        "input": inp,
        "output": out,
        "source": "provider",
    }
