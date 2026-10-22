struct process *get_current(void)
{
 int prio;
 @
UTRAP_ON_STAT();@
return (current_job);
}