int block(void)
{
 struct process *job;
 job = get_current();
 if (job) {@
return (enqueue(0, job));@
}
 return (0);
}