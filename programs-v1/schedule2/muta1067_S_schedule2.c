int block(void)
{
 struct process *job;
 @
 (current_job = get_current()) ; @

 if (job) {
  current_job = (struct process *)0;
  return (enqueue(0, job));
 }
 return (0);
}