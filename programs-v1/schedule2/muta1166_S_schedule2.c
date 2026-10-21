int quantum_expire(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  @
return (enqueue((-1) , job)) ;@

 }
 return (0);
}