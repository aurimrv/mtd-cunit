#!/usr/bin/env bash
# Collect mutant records → statistical RQ analysis → LaTeX report.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ANALYSIS="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROGRAMS_DIR="${1:-$ROOT/programs-v1}"
OUT_DIR="${2:-$ROOT/programs-v1/_analysis}"
PROGRAMS="${PROGRAMS:-boundedQueue,cal,UnixCal}"

PY=python3
if [ -x "$ROOT/.venv-analysis/bin/python" ]; then
  PY="$ROOT/.venv-analysis/bin/python"
elif ! "$PY" -c "import pandas,numpy,scipy" 2>/dev/null; then
  echo "Creating $ROOT/.venv-analysis (pandas/numpy/scipy)..."
  python3 -m venv "$ROOT/.venv-analysis"
  "$ROOT/.venv-analysis/bin/pip" install -q pandas numpy scipy
  PY="$ROOT/.venv-analysis/bin/python"
fi

mkdir -p "$OUT_DIR"

"$PY" "$ANALYSIS/collect_records.py" \
  --programs-dir "$PROGRAMS_DIR" \
  --programs "$PROGRAMS" \
  --out-csv "$OUT_DIR/mutant_records.csv"

"$PY" "$ANALYSIS/analyze_rqs.py" \
  --records-csv "$OUT_DIR/mutant_records.csv" \
  --out-json "$OUT_DIR/rq_results.json"

"$PY" "$ANALYSIS/generate_latex_report.py" \
  --results-json "$OUT_DIR/rq_results.json" \
  --out-tex "$OUT_DIR/rq_report.tex"

echo "Wrote:"
echo "  $OUT_DIR/mutant_records.csv"
echo "  $OUT_DIR/rq_results.json"
echo "  $OUT_DIR/rq_report.tex"
echo "Compile with: pdflatex -output-directory $OUT_DIR $OUT_DIR/rq_report.tex"
