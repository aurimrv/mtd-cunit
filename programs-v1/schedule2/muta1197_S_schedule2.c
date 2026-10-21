int quantum_expire(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  @
return (enqueue(TRAP_ON_POSITIVE((job->priority)) , job)) ;@

 }
 return (0);
}