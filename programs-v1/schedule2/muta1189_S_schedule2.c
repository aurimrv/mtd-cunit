int quantum_expire(void)
{
 struct process *job;
 job = get_current();
 if @
(UTRAP_ON_FALSE(@
(job)@
))@
 {
  current_job = (struct process *)0;
  return (enqueue(job->priority, job));
 }
 return (0);
}