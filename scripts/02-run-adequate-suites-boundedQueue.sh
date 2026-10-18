#!/usr/bin/env bash
# Thin wrapper: adequate suites for boundedQueue only.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TMP="$(mktemp)"
printf 'boundedQueue\n' >"$TMP"
trap 'rm -f "$TMP"' EXIT
exec "$ROOT/scripts/02-run-adequate-suites.sh" \
  --programs-dir "$ROOT/programs-v1" \
  --programs-file "$TMP" \
  "$@"
