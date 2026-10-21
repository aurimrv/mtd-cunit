void finish_process(void)
{
 schedule();
 if (cur_proc) {
  @
;@

  free_ele(cur_proc);
  num_processes--;
 }
}