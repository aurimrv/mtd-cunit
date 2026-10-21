void quantum_expire(void)
{
 int prio;
 schedule();
 if (cur_proc) {
  prio = cur_proc->priority;
  @
 (prio_queue[prio] = append_ele(prio_queue[alloc_proc_num] , cur_proc)) ; @

 }
}