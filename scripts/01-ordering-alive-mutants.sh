#!/bin/bash

#####################################################################
# 01-ordering-alive-mutants.sh
#   --programs-dir <path> --programs-file <path>
#   --order <random|ascending|descending>
#   [--seed <int>] [--operators-list <path>]
#####################################################################

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WORKER="${SCRIPT_DIR}/ordering-alive-mutants.py"
PROGRAMS_DIR=""
PROGRAMS_FILE=""
OPS_LIST="${SCRIPT_DIR}/unit-operators-list.txt"
ORDER=""
SEED=""

usage() {
  cat <<EOF
Usage: 01-ordering-alive-mutants.sh \\
         --programs-dir <path> \\
         --programs-file <path> \\
         --order <random|ascending|descending> \\
         [--seed <int>] \\
         [--operators-list <path>]

  --programs-dir      Root directory of programs under test
  --programs-file     File listing program directory names (one per line)
  --order             random | ascending | descending
  --seed              Required when --order random; ignored otherwise
  --operators-list    Optional (default: scripts/unit-operators-list.txt)
EOF
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --programs-dir)
      [ "$#" -ge 2 ] || { echo "error: --programs-dir requires a value" >&2; exit 1; }
      PROGRAMS_DIR=$2
      shift 2
      ;;
    --programs-file)
      [ "$#" -ge 2 ] || { echo "error: --programs-file requires a value" >&2; exit 1; }
      PROGRAMS_FILE=$2
      shift 2
      ;;
    --operators-list)
      [ "$#" -ge 2 ] || { echo "error: --operators-list requires a value" >&2; exit 1; }
      OPS_LIST=$2
      shift 2
      ;;
    --order)
      [ "$#" -ge 2 ] || { echo "error: --order requires a value" >&2; exit 1; }
      ORDER=$2
      shift 2
      ;;
    --seed)
      [ "$#" -ge 2 ] || { echo "error: --seed requires a value" >&2; exit 1; }
      SEED=$2
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "error: unknown argument: $1" >&2
      usage
      exit 1
      ;;
  esac
done

if [ -z "$PROGRAMS_DIR" ] || [ -z "$PROGRAMS_FILE" ] || [ -z "$ORDER" ]; then
  echo "error: --programs-dir, --programs-file, and --order are required" >&2
  usage
  exit 1
fi

case "$ORDER" in
  random|ascending|descending) ;;
  *)
    echo "error: --order must be random, ascending, or descending" >&2
    exit 1
    ;;
esac

if [ "$ORDER" = "random" ] && [ -z "$SEED" ]; then
  echo "error: --seed is required when --order random" >&2
  exit 1
fi

if [ ! -f "$WORKER" ]; then
  echo "error: worker not found: $WORKER" >&2
  exit 1
fi

cmd=("$WORKER"
  --programs-dir "$PROGRAMS_DIR"
  --programs-file "$PROGRAMS_FILE"
  --operators-list "$OPS_LIST"
  --order "$ORDER"
)

if [ -n "$SEED" ]; then
  cmd+=(--seed "$SEED")
fi

exec "${cmd[@]}"
