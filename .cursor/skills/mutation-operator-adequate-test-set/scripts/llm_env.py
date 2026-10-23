#!/usr/bin/env python3
"""Load LLM_GEN_MODELS / API_KEYS / API_URLS / LLM_EQUIV_MODEL from .env."""

from __future__ import annotations

import os
from dataclasses import dataclass
from pathlib import Path


def _parse_list(raw: str | None) -> list[str]:
    if raw is None:
        return []
    parts = [p.strip() for p in raw.split(",")]
    return [p for p in parts if p]


def _find_dotenv(start: Path | None = None) -> Path | None:
    override = os.environ.get("DOTENV_PATH", "").strip()
    if override:
        p = Path(override).expanduser().resolve()
        return p if p.is_file() else None
    cur = (start or Path.cwd()).resolve()
    for d in [cur, *cur.parents]:
        cand = d / ".env"
        if cand.is_file():
            return cand
        # stop at repo markers
        if (d / ".git").exists() or (d / ".env.example").exists():
            if cand.is_file():
                return cand
            # continue one more if .env.example only
            if (d / ".env").is_file():
                return d / ".env"
    return None


def load_dotenv_file(path: Path) -> dict[str, str]:
    out: dict[str, str] = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        if s.startswith("export "):
            s = s[len("export ") :].strip()
        if "=" not in s:
            continue
        key, _, val = s.partition("=")
        key = key.strip()
        val = val.strip()
        if (val.startswith('"') and val.endswith('"')) or (
            val.startswith("'") and val.endswith("'")
        ):
            val = val[1:-1]
        out[key] = val
    return out


@dataclass(frozen=True)
class LlmAttemptConfig:
    model: str
    api_key: str
    api_url: str


@dataclass(frozen=True)
class LlmEnvConfig:
    attempts: list[LlmAttemptConfig]
    equiv_model: str
    equiv_api_key: str
    equiv_api_url: str
    dotenv_path: Path | None

    @property
    def models(self) -> list[str]:
        return [a.model for a in self.attempts]


def _broadcast(values: list[str], n: int, name: str) -> list[str]:
    if not values:
        raise ValueError(f"{name} is empty; set it in .env")
    if len(values) == 1:
        return values * n
    if len(values) != n:
        raise ValueError(
            f"{name} length {len(values)} must be 1 or match "
            f"LLM_GEN_MODELS length {n}"
        )
    return values


def load_llm_env(start: Path | None = None) -> LlmEnvConfig:
    """Merge file .env into process env (file does not override existing env)."""
    dotenv = _find_dotenv(start)
    file_vars: dict[str, str] = {}
    if dotenv is not None:
        file_vars = load_dotenv_file(dotenv)

    def get(name: str) -> str | None:
        if name in os.environ and os.environ[name].strip():
            return os.environ[name]
        return file_vars.get(name)

    models = _parse_list(get("LLM_GEN_MODELS"))
    if not models:
        raise ValueError(
            "LLM_GEN_MODELS is required (comma-separated model ids in .env)"
        )
    keys = _broadcast(_parse_list(get("API_KEYS")), len(models), "API_KEYS")
    urls = _broadcast(_parse_list(get("API_URLS")), len(models), "API_URLS")

    attempts = [
        LlmAttemptConfig(model=m, api_key=k, api_url=u)
        for m, k, u in zip(models, keys, urls)
    ]
    for i, a in enumerate(attempts):
        if not a.api_key:
            raise ValueError(f"API_KEYS entry for attempt {i} is empty")
        if not a.api_url:
            raise ValueError(f"API_URLS entry for attempt {i} is empty")

    equiv_model = (get("LLM_EQUIV_MODEL") or models[-1]).strip()
    # Equiv uses first key/url (broadcast) or last attempt's credentials
    equiv_key = keys[0] if len(set(keys)) == 1 else keys[-1]
    equiv_url = urls[0] if len(set(urls)) == 1 else urls[-1]
    # Prefer matching equiv model index if present
    for a in attempts:
        if a.model == equiv_model:
            equiv_key, equiv_url = a.api_key, a.api_url
            break

    return LlmEnvConfig(
        attempts=attempts,
        equiv_model=equiv_model,
        equiv_api_key=equiv_key,
        equiv_api_url=equiv_url,
        dotenv_path=dotenv,
    )
