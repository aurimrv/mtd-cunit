void quantum_expire(void)
{
 int prio;
 schedule();
 if (cur_proc) {
  @
 (num_processes = (cur_proc->priority)) ; @

  prio_queue[prio] = append_ele(prio_queue[prio], cur_proc);
 }
}