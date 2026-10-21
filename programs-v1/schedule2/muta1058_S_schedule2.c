int block(void)
{
 struct process *job;
 job = get_current();
 if @
(UTRAP_ON_TRUE(@
(job)@
))@
 {
  current_job = (struct process *)0;
  return (enqueue(0, job));
 }
 return (0);
}