int reschedule(int prio)
{
 if @
( (current_job && (__MININT__ > (current_job->priority))) )@
 {
  put_end(current_job->priority, current_job);
  current_job = (struct process *)0;
 }
 get_current();
 return (0);
}