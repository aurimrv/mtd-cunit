int block(void)
{
 struct process *job;
 job = get_current();
 if (job) {@
UTRAP_ON_STAT();@
 }
 return (0);
}