struct process *get_current(void)
{
 int prio;
 if (!current_job) {
  for (prio = 3; prio > 0; prio--) {@
UTRAP_ON_STAT();@
 }
 }
 return (current_job);
}