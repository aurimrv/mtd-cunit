int block(void)
{
 struct process *job;
 job = get_current();
 @
return (enqueue(0, job));@
return (0);
}