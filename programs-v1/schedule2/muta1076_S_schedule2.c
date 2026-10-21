int unblock(float ratio)
{
 int status;
 struct process *job;
 if @
( ((status = get_process(0 , (-1.0) , (& job))) <= 0) )@

  return (status);
 return (enqueue(job->priority, job));
}