Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 ((proc->priority) = __MININT__) ;@

 num_processes++;
 return proc;
}