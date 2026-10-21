Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 (alloc_proc_num = prio) ; @

 num_processes++;
 return proc;
}