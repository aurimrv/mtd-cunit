struct process *get_current(void)
{
 int prio;
 if (!current_job) {
  for (prio = 3; prio > 0; prio--) {
   if @
( (get_process(TRAP_ON_NEGATIVE(prio) , 0.0 , (& current_job)) > 0) )@

    break;
  }
 }
 return (current_job);
}