int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  reschedule(0);
  @
return (0);@

  free(job);
  return (0);
 } else
  return (1);
}