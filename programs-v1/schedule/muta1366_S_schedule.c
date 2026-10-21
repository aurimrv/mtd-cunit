void add_process(int prio)
{
 Ele *proc;
 @
 (proc = new_process(1)) ;@

 prio_queue[prio] = append_ele(prio_queue[prio], proc);
}