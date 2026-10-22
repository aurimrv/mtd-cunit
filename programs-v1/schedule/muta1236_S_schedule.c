void quantum_expire(void)
{
 int prio;
 schedule();
 if (cur_proc) {
  prio = cur_proc->priority;
  @
 (prio_queue[1] = append_ele(prio_queue[prio] , cur_proc)) ;@

 }
}