#!/usr/bin/env bash
# Reopen high-rate u-SSDL EQUIVALENT mutants and re-run invent (keep KILLED).
#
# Usage:
#   03-rerun-ssdl-high-equiv.sh --programs-dir programs-v1 [--jobs N] [--min-equiv-rate 0.25]
#
# Improvements in invent/run_attempt are program-agnostic; this only selects by
# operator status metrics.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROGRAMS_DIR=""
MIN_RATE="${MIN_EQUIV_RATE:-0.25}"
JOBS="${JOBS:-4}"
EXCLUDE="${EXCLUDE:-replace}"
ONLY="${ONLY:-}"
LLM_NAME="${LLM_NAME:-composer-ssdl-rerun-v1}"
MAX_ITER="${MAX_ITERATIONS:-5}"
SKILL="${ROOT}/.cursor/skills/mutation-operator-adequate-test-set/scripts"
DRY_RUN=0

usage() {
  cat <<EOF
Usage: $0 --programs-dir <path> [--jobs N] [--min-equiv-rate 0.25]
          [--exclude replace] [--only prog1,prog2] [--dry-run]
EOF
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --programs-dir) PROGRAMS_DIR=$2; shift 2 ;;
    --jobs) JOBS=$2; shift 2 ;;
    --min-equiv-rate) MIN_RATE=$2; shift 2 ;;
    --exclude) EXCLUDE=$2; shift 2 ;;
    --only) ONLY=$2; shift 2 ;;
    --dry-run) DRY_RUN=1; shift ;;
    -h|--help) usage; exit 0 ;;
    *) echo "error: unknown $1" >&2; usage; exit 1 ;;
  esac
done

if [ -z "$PROGRAMS_DIR" ]; then
  echo "error: --programs-dir required" >&2
  usage
  exit 1
fi
PROGRAMS_DIR="$(cd "$PROGRAMS_DIR" && pwd)"
export PATH="${PROTEUMIMHOME:-/home/auri/Documentos/testingtools/ProteumIM64/bin}:${PATH}"
# Prefer real GNU timeout (PATH may shadow with a broken local timeout)
TIMEOUT_BIN="$(command -v /usr/bin/timeout || command -v timeout)"

LOG_ROOT="${PROGRAMS_DIR}/_logs/ssdl-rerun"
mkdir -p "$LOG_ROOT"
LIST="${LOG_ROOT}/programs-selected.txt"

REOPEN_ARGS=(
  --programs-dir "$PROGRAMS_DIR"
  --operator u-SSDL
  --min-equiv-rate "$MIN_RATE"
  --exclude "$EXCLUDE"
  --list-out "$LIST"
)
[ -n "$ONLY" ] && REOPEN_ARGS+=(--only "$ONLY")
[ "$DRY_RUN" -eq 1 ] && REOPEN_ARGS+=(--dry-run)

echo "=== reopen scan ==="
python3 "${SKILL}/reopen_ssdl_equivalents.py" "${REOPEN_ARGS[@]}" \
  | tee "${LOG_ROOT}/reopen.json"

if [ "$DRY_RUN" -eq 1 ]; then
  echo "dry-run only; not launching workers"
  exit 0
fi

if [ ! -s "$LIST" ]; then
  echo "no programs selected"
  exit 0
fi

run_one() {
  local PROG="$1"
  local PROG_DIR="${PROGRAMS_DIR}/${PROG}"
  local SESSION="S_${PROG}"
  local LOG="${LOG_ROOT}/${PROG}.log"
  {
    echo "########## SSDL RERUN ${PROG} $(date -Is) ##########"
    cd "$PROG_DIR"
    if [ -f compile_cunit.txt ]; then
      bash -c "$(cat compile_cunit.txt)" || true
    fi
    python3 "${SKILL}/run_operator.py" \
      --program-dir "$PROG_DIR" \
      --operator u-SSDL \
      --session "$SESSION" \
      --max-iterations "$MAX_ITER" \
      --llm-name "$LLM_NAME" \
      --invent-mutation-directed \
      --resume \
      --skip-if-done
    python3 "${SKILL}/summarize_status.py" --program-dir "$PROG_DIR" || true
    echo "########## END ${PROG} $(date -Is) ##########"
  } >"$LOG" 2>&1
  echo "done ${PROG} -> ${LOG}"
}

export -f run_one
export PROGRAMS_DIR SKILL LLM_NAME MAX_ITER LOG_ROOT

echo "=== launching up to ${JOBS} parallel SSDL reruns ==="
# xargs -P: one program per worker
xargs -a "$LIST" -P "$JOBS" -n 1 -I{} bash -c 'run_one "$@"' _ {}

echo "=== all workers finished ==="
python3 - <<PY
import json
from pathlib import Path
from collections import Counter
root = Path("${PROGRAMS_DIR}")
list_path = Path("${LIST}")
progs = [ln.strip() for ln in list_path.read_text().splitlines() if ln.strip()]
print(f"{'program':22} {'K':>5} {'E':>5} {'A':>5} equiv%")
for name in progs:
    p = root / name / "mutants" / "u-SSDL_execution_status.json"
    if not p.exists():
        print(f"{name:22} (no status)")
        continue
    d = json.loads(p.read_text())
    cc = Counter((m.get("status") or "?").upper() for m in d.get("mutants") or [])
    fin = cc["KILLED"] + cc["EQUIVALENT"]
    rate = 100 * cc["EQUIVALENT"] / fin if fin else 0
    print(f"{name:22} {cc['KILLED']:5} {cc['EQUIVALENT']:5} {cc['ALIVE']:5} {rate:5.1f}%")
PY
