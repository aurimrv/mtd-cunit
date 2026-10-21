void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , alloc_proc_num)) ; @

  free_ele(cur_proc);
  num_processes--;
 }
}