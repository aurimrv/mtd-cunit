Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
 ((proc->val) = prio) ;@

 num_processes++;
 return proc;
}