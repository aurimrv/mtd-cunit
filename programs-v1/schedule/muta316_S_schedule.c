void finish_process(void)
{
 @
;@

 if (cur_proc) {
  fprintf(stdout, "%d ", cur_proc->val);
  free_ele(cur_proc);
  num_processes--;
 }
}