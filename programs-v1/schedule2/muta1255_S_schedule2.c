int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {@
UTRAP_ON_STAT();@
 } else
  return (1);
}