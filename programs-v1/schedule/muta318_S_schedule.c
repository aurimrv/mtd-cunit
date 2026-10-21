void finish_process(void)
{
 schedule();
 if (cur_proc) {
  fprintf(stdout, "%d ", cur_proc->val);
  @
;@

  num_processes--;
 }
}