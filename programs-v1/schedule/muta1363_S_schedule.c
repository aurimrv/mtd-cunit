Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 ((proc->priority) = PRED(prio)) ;@

 num_processes++;
 return proc;
}