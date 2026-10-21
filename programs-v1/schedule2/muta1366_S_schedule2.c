struct process *get_current(void)
{
 int prio;
 if (!current_job) {
  for (prio = 3; prio > 0; prio--) {@
return (current_job);@
}
 }
 return (current_job);
}