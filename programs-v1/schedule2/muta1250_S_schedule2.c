int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  @
UTRAP_ON_STAT();@

  reschedule(0);
  fprintf(stdout, " %d", job->pid);
  free(job);
  return (0);
 } else
  return (1);
}