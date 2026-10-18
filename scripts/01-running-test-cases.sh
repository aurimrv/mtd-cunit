#!/bin/bash

#####################################################################
# 00-create-test-session.sh <programs_base_dir> <programs_file_names>
#####################################################################


if [ "$#" -ne 2 ]
then
  echo "Usage: 00-create-test-session.sh <projects root directory> <file with directory names to be tested>"
  exit 1
else
   EXPER_HOME=$1
   FILES=$2

   OUTTN=script-test-new.out
   OUTMG=script-muta-gen.out
   OUTTC=script-tcase-add.out
   OUTRE=report
   OUTEQ=script-equivalent.txt
   CMDTIME=script-execution-time.csv
   for PROG in $(cat ${EXPER_HOME}/$FILES)
   do
      SESSION=S_$PROG

      # Compiling source code
      cd $EXPER_HOME/$PROG

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
      test-new -S $PROG -E $PROG -C "$compilation" $SESSION &> $OUTTN
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
      compilation=$(cat compile_cunit_instrum.txt)
      $compilation
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";END gcc instrum" >> $CMDTIME

      # Generating all possible unit mutants
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";START muta-gen" >> $CMDTIME
      functions=$(cat functions.txt | awk '{printf("-unit %s ", $1)}')
      muta-gen $functions -u- 1.0 0 $SESSION &> $OUTMG
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";END muta-gen" >> $CMDTIME

      # Initial report
      exemuta -exec -v . -trace $SESSION
      report -tcase -S ${OUTRE}-initial $SESSION

      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";START tcase-add" >> $CMDTIME
      # Importar casos de teste
      tc=1
      NTC=$(wc -l testset.txt | awk '{print $1}')
      while [ $tc -le $NTC ]; 
      do
         param=$(head -$tc testset.txt | tail -1)
         echo "Importing TC $tc of $NTC - param: $param"
         tcase-add -p "$param" -EE ${PROG}_inst -trace $SESSION
         tc=$((tc + 1))
      done
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";END tcase-add" >> $CMDTIME

      tcase -l $SESSION &> $OUTTC

      # Executar Mutantes
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";START exemuta" >> $CMDTIME

      exemuta -exec -v . -trace $SESSION

      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";END exemuta" >> $CMDTIME

      # All live mutants are equivalent
      mv equivalent-${PROG}.txt equivalent-${PROG}.bkp
      muta -l $SESSION | info-muta -alive > equivalent-${PROG}.txt

      # Geração do Relatório
      report -tcase -S ${OUTRE}-live $SESSION

      # Marcando Mutantes Equivalentes
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";START muta -equiv" >> $CMDTIME
      equivalents=$(cat equivalent-${PROG}.txt)
      muta -equiv -x "$equivalents" $SESSION
      exemuta -exec -v . -trace $SESSION
      date --rfc-3339=ns |tr -d "\n" >> $CMDTIME
      echo ";END muta -equiv" >> $CMDTIME

      # Geração do Relatório
      report -tcase -S ${OUTRE}-final $SESSION
   done
fi