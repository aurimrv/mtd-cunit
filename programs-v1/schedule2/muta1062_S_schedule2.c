int block(void)
{
 struct process *job;
 job = get_current();
 if (job) {
  current_job = (struct process *)0;
  @
UTRAP_ON_STAT();@

 }
 return (0);
}