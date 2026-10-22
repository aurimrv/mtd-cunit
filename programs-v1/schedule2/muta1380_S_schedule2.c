struct process *get_current(void)
{
 int prio;
 if @
(UTRAP_ON_FALSE(@
(!current_job)@
))@
 {
  for (prio = 3; prio > 0; prio--) {
   if (get_process(prio, 0.0, &current_job) > 0)
    break;
  }
 }
 return (current_job);
}