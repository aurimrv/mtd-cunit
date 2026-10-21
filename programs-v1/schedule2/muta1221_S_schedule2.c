int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  @
return (0);@

  reschedule(0);
  fprintf(stdout, " %d", job->pid);
  free(job);
  return (0);
 } else
  return (1);
}