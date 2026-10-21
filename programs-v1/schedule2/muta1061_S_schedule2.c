int block(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  @
UTRAP_ON_STAT();@

  return (enqueue(0, job));
 }
 return (0);
}