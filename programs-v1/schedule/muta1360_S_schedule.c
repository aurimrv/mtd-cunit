Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 (prio = prio) ; @

 num_processes++;
 return proc;
}