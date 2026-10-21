int block(void)
{
 struct process *job;
 @
;@

 if (job) {
  current_job = (struct process *)0;
  return (enqueue(0, job));
 }
 return (0);
}