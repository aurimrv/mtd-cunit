Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 ((proc->priority) = num_processes) ; @

 num_processes++;
 return proc;
}