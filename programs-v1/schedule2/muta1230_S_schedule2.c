int finish(void)
{
 struct process *job;
 job = get_current();
 if (job) {@
return (0);@
} else
  return (1);
}