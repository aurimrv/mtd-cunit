int upgrade_prio(int prio, float ratio)
{
 int status;
 struct process *job;
 if (prio < 1 || prio > 2)
  return (-4);
 if @
( ((status /= get_process(prio , ratio , (& job))) <= 0) )@

  return (status);
 job->priority = prio + 1;
 return (enqueue(prio + 1, job));
}