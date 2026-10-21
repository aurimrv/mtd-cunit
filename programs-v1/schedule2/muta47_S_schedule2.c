int enqueue(int prio, struct process *new_process)
{
 int status;
 if (status = put_end(prio, new_process))
  return (status);
 @
return (reschedule(TRAP_ON_POSITIVE(prio))) ;@

}