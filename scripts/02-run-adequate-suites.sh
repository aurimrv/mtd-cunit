#!/usr/bin/env bash
# Run operator-adequate suites for each program listed in --programs-file.
#
# IMPORTANT: automated reuse of ts_data killing tests is DISABLED.
# Default: --mutation-oriented-input-generation (heuristic NEW inputs from
# Get on: + schema; oracles via CUNIT_CAPTURE; no LLM). Or supply LLM rows
# via candidates JSONL.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROGRAMS_DIR=""
PROGRAMS_FILE=""
OPS_LIST="${ROOT}/scripts/unit-operators-list.txt"
SKILL="${ROOT}/.cursor/skills/mutation-operator-adequate-test-set/scripts"
MAX_ITER="${MAX_ITERATIONS:-5}"
LLM_NAME="${LLM_NAME:-composer-mutation-directed-v1}"

usage() {
  cat <<EOF
Usage: 02-run-adequate-suites.sh \\
         --programs-dir <path> \\
         --programs-file <path> \\
         [--operators-list <path>]

Environment:
  MAX_ITERATIONS   default 5
  LLM_NAME         default composer-mutation-directed-v1
EOF
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --programs-dir)
      PROGRAMS_DIR=$2; shift 2 ;;
    --programs-file)
      PROGRAMS_FILE=$2; shift 2 ;;
    --operators-list)
      OPS_LIST=$2; shift 2 ;;
    -h|--help)
      usage; exit 0 ;;
    *)
      echo "error: unknown argument: $1" >&2
      usage
      exit 1
      ;;
  esac
done

if [ -z "$PROGRAMS_DIR" ] || [ -z "$PROGRAMS_FILE" ]; then
  echo "error: --programs-dir and --programs-file are required" >&2
  usage
  exit 1
fi

export PATH="${PROTEUMIMHOME:-/home/auri/Documentos/testingtools/ProteumIM64/bin}:${PATH}"

mapfile -t PROG_LINES <"$PROGRAMS_FILE"
for raw in "${PROG_LINES[@]}"; do
  PROG="${raw%%#*}"
  PROG="$(echo "$PROG" | tr -d '[:space:]')"
  [ -z "$PROG" ] && continue

  PROG_DIR="${PROGRAMS_DIR}/${PROG}"
  SESSION="S_${PROG}"
  LOG_DIR="${PROG_DIR}/mutants/adequate-run-logs"
  mkdir -p "$LOG_DIR"

  echo "########## PROGRAM ${PROG} ##########"
  echo "Ordering alive mutant lists..."
  printf '%s\n' "$PROG" >"${LOG_DIR}/programs.txt"
  "${ROOT}/scripts/01-ordering-alive-mutants.sh" \
    --programs-dir "$PROGRAMS_DIR" \
    --programs-file "${LOG_DIR}/programs.txt" \
    --order ascending \
    --operators-list "$OPS_LIST"

  cd "$PROG_DIR"
  bash -c "$(cat compile_cunit.txt)"
  bash compile_cunit_instrum.txt

  mapfile -t OP_LINES <"$OPS_LIST"
  for line in "${OP_LINES[@]}"; do
    line="${line%%#*}"
    line="$(echo "$line" | tr -d '[:space:]')"
    [ -z "$line" ] && continue
    case "$line" in
      *,*) ;;
      *) continue ;;
    esac
    code="${line%%,*}"
    op="${line#*,}"
    case "$code" in
      ''|*[!0-9]*) continue ;;
    esac
    alive_file="${PROG_DIR}/mutants/${op}.txt"
    [ -f "$alive_file" ] || continue
    n="$(grep -c '^[0-9]' "$alive_file" 2>/dev/null || true)"
    n="$(echo "$n" | head -n1 | tr -d '[:space:]')"
    if [ -z "$n" ] || [ "$n" -eq 0 ]; then
      if [ -f "${PROG_DIR}/mutants/${op}_execution_status.json" ]; then
        echo "SKIP ${PROG}/${op} (no alive; status exists)"
      else
        echo "SKIP ${PROG}/${op} (no mutants)"
      fi
      continue
    fi
    echo "===== START ${PROG}/${op} (alive=${n}) ====="
    python3 "${SKILL}/run_operator.py" \
      --program-dir "$PROG_DIR" \
      --operator "$op" \
      --session "$SESSION" \
      --max-iterations "$MAX_ITER" \
      --llm-name "$LLM_NAME" \
      --mutation-oriented-input-generation \
      --skip-if-done \
      </dev/null \
      2>&1 | tee "${LOG_DIR}/${op}.log"
    echo "===== END ${PROG}/${op} ====="
    python3 "${SKILL}/summarize_status.py" --program-dir "$PROG_DIR" </dev/null >/dev/null || true
  done

  python3 "${SKILL}/summarize_status.py" --program-dir "$PROG_DIR"
  echo "Done ${PROG}. Summary: ${PROG_DIR}/mutants/adequate-suite-summary.json"
done
