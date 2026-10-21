void finish_all_processes(void)
{
 int i;
 int total;
 @
 (total = 1) ;@

 for (i = 0; i < total; i++)
  finish_process();
}