void finish_all_processes(void)
{
 int i;
 int total;
 @
 (total = SUCC(num_processes)) ;@

 for (i = 0; i < total; i++)
  finish_process();
}