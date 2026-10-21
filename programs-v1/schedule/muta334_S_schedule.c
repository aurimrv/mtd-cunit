void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , TRAP_ON_ZERO((cur_proc->val)))) ;@

  free_ele(cur_proc);
  num_processes--;
 }
}