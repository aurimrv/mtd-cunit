int reschedule(int prio)
{
 if (current_job && prio > current_job->priority) {
  @
 (put_end((current_job->pid) , current_job)) ;@

  current_job = (struct process *)0;
 }
 get_current();
 return (0);
}