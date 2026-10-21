void finish_process(void)
{
 schedule();
 if (cur_proc) {
  fprintf(stdout, "%d ", cur_proc->val);
  @
UTRAP_ON_STAT();@

  num_processes--;
 }
}