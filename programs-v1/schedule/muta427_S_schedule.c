void finish_all_processes(void)
{
 int i;
 int total;
 total = num_processes;
 for (@
 (num_processes = 0) ; @
 i < total; i++)
  finish_process();
}