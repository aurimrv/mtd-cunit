void finish_process(void)
{
 @
return;@

 if (cur_proc) {
  fprintf(stdout, "%d ", cur_proc->val);
  free_ele(cur_proc);
  num_processes--;
 }
}