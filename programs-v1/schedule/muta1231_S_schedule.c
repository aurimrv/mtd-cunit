void quantum_expire(void)
{
 int prio;
 schedule();
 if (cur_proc) {
  @
 (prio = 1) ;@

  prio_queue[prio] = append_ele(prio_queue[prio], cur_proc);
 }
}