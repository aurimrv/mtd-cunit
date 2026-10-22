int put_end(int prio, struct process *process)
{
 struct process **next;
 if (prio > 3 || prio < 0)
  return (-4);
 for (@
 (next = (& (prio_queue[(-1)].head))) ;@
 *next; next = &(*next)->next) ;
 *next = process;
 prio_queue[prio].length++;
 return (0);
}