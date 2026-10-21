void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
UTRAP_ON_STAT();@

  free_ele(cur_proc);
  num_processes--;
 }
}