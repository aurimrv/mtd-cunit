void finish_all_processes(void)
{
 int i;
 int total;
 @
 (total = TRAP_ON_NEGATIVE(num_processes)) ;@

 for (i = 0; i < total; i++)
  finish_process();
}