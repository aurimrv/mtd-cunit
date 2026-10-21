int block(void)
{
 struct process *job;
 @
UTRAP_ON_STAT();@

 if (job) {
  current_job = (struct process *)0;
  return (enqueue(0, job));
 }
 return (0);
}