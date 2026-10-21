void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , __MININT__)) ;@

  free_ele(cur_proc);
  num_processes--;
 }
}