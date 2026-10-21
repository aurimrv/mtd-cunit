int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  @
UTRAP_ON_STAT();@

  fprintf(stdout, " %d", job->pid);
  free(job);
  return (0);
 } else
  return (1);
}