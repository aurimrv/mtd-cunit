void quantum_expire(void)
{
 int prio;
 schedule();
 if (cur_proc) {
  @
 (prio = alloc_proc_num) ; @

  prio_queue[prio] = append_ele(prio_queue[prio], cur_proc);
 }
}