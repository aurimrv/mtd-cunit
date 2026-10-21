void add_process(int prio)
{
 Ele *proc;
 proc = new_process(prio);
 @
 (prio_queue[prio] = append_ele(prio_queue[0] , proc)) ;@

}