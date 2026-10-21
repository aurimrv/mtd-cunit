void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
 (fprintf(stdout , "%d " , __MAXINT__)) ;@

  free_ele(cur_proc);
  num_processes--;
 }
}