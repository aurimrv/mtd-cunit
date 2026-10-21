int get_process(int prio, float ratio, struct process **job)
{
 int length, index;
 struct process **next;
 if (prio > 3 || prio < 0)
  return (-4);
 if (ratio < 0.0 || ratio > 1.0)
  return (-5);
 length = prio_queue[prio].length;
 index = ratio * length;
 index = index >= length ? length - 1 : index;
 for (@
 (next = (& (prio_queue[1].head))) ;@
 index && *next; index--)
  next = &(*next)->next;
 *job = *next;
 if (*job) {
  *next = (*next)->next;
  (*job)->next = (struct process *)0;
  prio_queue[prio].length--;
  return (1);
 } else
  return (0);
}