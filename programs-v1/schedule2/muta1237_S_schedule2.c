int finish(void)
{
 struct process *job;
 @
;@

 if (job) {
  current_job = (struct process *)0;
  reschedule(0);
  fprintf(stdout, " %d", job->pid);
  free(job);
  return (0);
 } else
  return (1);
}