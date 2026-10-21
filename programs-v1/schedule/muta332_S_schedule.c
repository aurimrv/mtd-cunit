void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , TRAP_ON_POSITIVE((cur_proc->val)))) ;@

  free_ele(cur_proc);
  num_processes--;
 }
}