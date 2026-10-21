int block(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  @
 (job = ((struct process (*)) 0) ) ; @

  return (enqueue(0, job));
 }
 return (0);
}