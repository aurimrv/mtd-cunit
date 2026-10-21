int quantum_expire(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  @
return (0);@

  return (enqueue(job->priority, job));
 }
 return (0);
}