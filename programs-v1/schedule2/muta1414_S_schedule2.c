int reschedule(int prio)
{
 if @
( (current_job && (prio > 0)) )@
 {
  put_end(current_job->priority, current_job);
  current_job = (struct process *)0;
 }
 get_current();
 return (0);
}