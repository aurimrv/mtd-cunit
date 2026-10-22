int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  reschedule(0);
  fprintf(stdout, " %d", job->pid);
  @
;@

  return (0);
 } else
  return (1);
}