#!/bin/bash

#####################################################################
# 00-create-test-session.sh
#   --programs-dir <path> --programs-file <path>
#   [--operators-list <path>]
#####################################################################

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROGRAMS_DIR=""
PROGRAMS_FILE=""
OPS_LIST="${SCRIPT_DIR}/unit-operators-list.txt"

usage() {
  cat <<EOF
Usage: 00-create-test-session.sh \\
         --programs-dir <path> \\
         --programs-file <path> \\
         [--operators-list <path>]

  --programs-dir      Root directory of programs under test
  --programs-file     File listing program directory names (one per line)
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

if [ -z "$PROGRAMS_DIR" ] || [ -z "$PROGRAMS_FILE" ]; then
  echo "error: --programs-dir and --programs-file are required" >&2
  usage
  exit 1
fi

EXPER_HOME=$PROGRAMS_DIR
FILES=$PROGRAMS_FILE

OUTTN=script-test-new.out
OUTMG=script-muta-gen.out
OUTTC=script-tcase-add.out
OUTRE=report
OUTEQ=script-equivalent.txt
CMDTIME=script-execution-time.csv

for PROG in $(cat "$FILES")
do
   SESSION=S_$PROG

   # Compiling source code
   cd "$EXPER_HOME/$PROG"

   # Compiling original source code
   date --rfc-3339=ns |tr -d "\n" > $CMDTIME
   echo ";START gcc" >> $CMDTIME
   compilation=$(cat compile_cunit.txt)
   $compilation
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";END gcc" >> $CMDTIME

   # Creating test session in test mode
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";START test-new" >> $CMDTIME
   # -E must match the "-o <name>" in compile_cunit.txt (runner). A mismatch
   # makes Proteum fail to substitute the executable name → all mutants Anomalous.
   test-new -S $PROG -E runner -C "$compilation" $SESSION &> $OUTTN
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";END test-new" >> $CMDTIME

   # Creating instrumented source code version
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";START instrum" >> $CMDTIME
   instrum -EE $SESSION __${PROG}
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";START instrum" >> $CMDTIME

   # Compiling instrumented code
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";START gcc instrum" >> $CMDTIME
   bash compile_cunit_instrum.txt
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";END gcc instrum" >> $CMDTIME

   # Generating all possible unit mutants
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";START muta-gen" >> $CMDTIME
   functions=$(cat functions.txt | awk '{printf("-unit %s ", $1)}')
   muta-gen $functions -u- 1.0 0 $SESSION &> $OUTMG
   date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
   echo ";END muta-gen" >> $CMDTIME

   # Initial report (exemuta needs a TTY for tcgetattr)
   script -q -e -c "exemuta -exec -v . -trace $SESSION" /dev/null
   report -tcase -S ${OUTRE}-initial $SESSION

   # Per-operator mutant IDs and totals
   mkdir -p mutants
   rm -f mutants/*.txt mutants/total-mutants-per-operator.csv
   muta -l $SESSION >& mutants.txt
   awk -F',' '
      NR == FNR {
         if (NR == 1 && $1 !~ /^[0-9]+$/) next
         gsub(/^[ \t]+|[ \t]+$/, "", $1)
         gsub(/^[ \t]+|[ \t]+$/, "", $2)
         ops[++n] = $2
         code[$2] = $1
         count[$2] = 0
         next
      }
      match($0, /^MUTANT # ([0-9]+)/, m) {
         cur = m[1]
         next
      }
      match($0, /Operator: [0-9]+ \(([^)]+)\)/, a) {
         op = a[1]
         count[op]++
         ids[op] = (ids[op] == "" ? cur : ids[op] ORS cur)
      }
      END {
         print "OP_CODE,OP_ACRONYM,TOTAL" > "mutants/total-mutants-per-operator.csv"
         for (i = 1; i <= n; i++) {
            op = ops[i]
            c = count[op] + 0
            f = "mutants/" op ".txt"
            if (c > 0)
               print ids[op] > f
            else
               printf "" > f
            close(f)
            print code[op] "," op "," c >> "mutants/total-mutants-per-operator.csv"
         }
      }
   ' "$OPS_LIST" mutants.txt
done
