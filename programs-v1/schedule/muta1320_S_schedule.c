Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 ((proc->priority) = 1) ;@

 num_processes++;
 return proc;
}