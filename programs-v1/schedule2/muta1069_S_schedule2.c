int block(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  @
return (enqueue(0 , current_job)) ; @

 }
 return (0);
}