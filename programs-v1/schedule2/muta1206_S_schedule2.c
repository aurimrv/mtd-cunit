int quantum_expire(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  @
return (enqueue((job->pid) , job)) ;@

 }
 return (0);
}