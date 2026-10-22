Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 proc->priority = prio;
 @
UTRAP_ON_STAT();@

 return proc;
}