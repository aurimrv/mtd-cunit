void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , 1)) ;@

  free_ele(cur_proc);
  num_processes--;
 }
}