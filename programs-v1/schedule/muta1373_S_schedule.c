void add_process(int prio)
{
 Ele *proc;
 proc = new_process(prio);
 @
 (prio_queue[__MAXINT__] = append_ele(prio_queue[prio] , proc)) ;@

}