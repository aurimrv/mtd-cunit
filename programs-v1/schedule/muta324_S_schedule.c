void finish_process(void)
{
 schedule();
 if @
(UTRAP_ON_FALSE(@
(cur_proc)@
))@
 {
  fprintf(stdout, "%d ", cur_proc->val);
  free_ele(cur_proc);
  num_processes--;
 }
}