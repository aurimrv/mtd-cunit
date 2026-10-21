void finish_all_processes(void)
{
 int i;
 int total;
 total = num_processes;
 for (i = 0; @
 (i < num_processes) ; @
 i++)
  finish_process();
}