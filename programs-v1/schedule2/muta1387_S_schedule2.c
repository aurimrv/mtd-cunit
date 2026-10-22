struct process *get_current(void)
{
 int prio;
 if (!current_job) {@
UTRAP_ON_STAT();@
 }
 return (current_job);
}