int quantum_expire(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  @
return (enqueue(job->priority, job));@

  return (enqueue(job->priority, job));
 }
 return (0);
}