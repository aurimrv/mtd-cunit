void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , num_processes)) ; @

  free_ele(cur_proc);
  num_processes--;
 }
}