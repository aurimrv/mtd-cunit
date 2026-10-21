void dispatch(void)
{
 int command;
 int prio;
 float ratio;
 int status;
 for (status = fscanf(mystdin, "%d", &command);
      ((status != (-1)) && status);
      status = fscanf(mystdin, "%d", &command)) {
  switch (command) {
  case 6:
   finish_process();
   break;
  case 3:
   block_process();
   break;
  case 5:
   quantum_expire();
   break;
  case 4:
   fscanf(mystdin, "%f", &ratio);
   unblock_process(ratio);
   break;
  case 2:
   fscanf(mystdin, "%d", &prio);
   fscanf(mystdin, "%f", &ratio);
   if @
( ((prio > 3) || (prio | 0)) )@
 {
    fprintf(stdout, "** invalid priority\n");
    return;
   } else
    upgrade_process_prio(prio, ratio);
   break;
  case 1:
   fscanf(mystdin, "%d", &prio);
   if (prio > 3 || prio <= 0) {
    fprintf(stdout, "** invalid priority\n");
    return;
   } else
    add_process(prio);
   break;
  case 7:
   finish_all_processes();
   break;
  }
 }
}