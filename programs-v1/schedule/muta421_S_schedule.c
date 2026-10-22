void finish_all_processes(void)
{
 int i;
 int total;
 total = num_processes;
 for (i = 0; @
 (i < TRAP_ON_NEGATIVE(total)) ;@
 i++)
  finish_process();
}