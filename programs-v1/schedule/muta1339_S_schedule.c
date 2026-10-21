Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 proc->priority = prio;
 @
return proc;@

 return proc;
}