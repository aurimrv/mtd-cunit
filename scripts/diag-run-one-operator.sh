#!/usr/bin/env bash
# Run a single program/operator in isolation with a wall-clock timeout.
# Usage:
#   diag-run-one-operator.sh --program CheckPalindrome --operator u-CRCR [--limit 3] [--timeout 180]
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROG=""
OP=""
LIMIT="${LIMIT_MUTANTS:-3}"
TIMEOUT_SEC="${TIMEOUT_SEC:-180}"
SKILL="$ROOT/.cursor/skills/mutation-operator-adequate-test-set/scripts"
PROGRAMS_DIR="$ROOT/programs-v1"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --program) PROG=$2; shift 2 ;;
    --operator) OP=$2; shift 2 ;;
    --limit) LIMIT=$2; shift 2 ;;
    --timeout) TIMEOUT_SEC=$2; shift 2 ;;
    --programs-dir) PROGRAMS_DIR=$2; shift 2 ;;
    *) echo "unknown arg: $1" >&2; exit 1 ;;
  esac
done

if [ -z "$PROG" ] || [ -z "$OP" ]; then
  echo "usage: $0 --program <name> --operator <OP> [--limit N] [--timeout SEC]" >&2
  exit 1
fi

if [ ! -f "${ROOT}/.env" ] && [ -z "${DOTENV_PATH:-}" ]; then
  echo "error: missing ${ROOT}/.env (copy from .env.example)" >&2
  exit 1
fi

export PATH="${PROTEUMIMHOME:-/home/auri/Documentos/testingtools/ProteumIM64/bin}:${PATH}"
export DOTENV_PATH="${DOTENV_PATH:-${ROOT}/.env}"
PROG_DIR="$PROGRAMS_DIR/$PROG"
LOG_DIR="$PROG_DIR/mutants/adequate-run-logs"
mkdir -p "$LOG_DIR"
LOG="$LOG_DIR/diag-${OP}.log"

cd "$PROG_DIR"
bash -c "$(cat compile_cunit.txt)"
bash compile_cunit_instrum.txt

echo "DIAG START $(date --rfc-3339=seconds) prog=$PROG op=$OP limit=$LIMIT timeout=${TIMEOUT_SEC}s" | tee "$LOG"
set +e
/usr/bin/timeout --signal=TERM --kill-after=30 "${TIMEOUT_SEC}" \
  python3 "$SKILL/run_operator.py" \
    --program-dir "$PROG_DIR" \
    --operator "$OP" \
    --session "S_${PROG}" \
    --dotenv-dir "$ROOT" \
    --skip-if-done \
    --limit-mutants "$LIMIT" \
    </dev/null >>"$LOG" 2>&1
rc=$?
set -e
echo "DIAG END $(date --rfc-3339=seconds) exit=$rc" | tee -a "$LOG"
exit "$rc"
