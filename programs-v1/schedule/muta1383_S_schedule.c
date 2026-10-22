void add_process(int prio)
{
 Ele *proc;
 @
;@

 prio_queue[prio] = append_ele(prio_queue[prio], proc);
}