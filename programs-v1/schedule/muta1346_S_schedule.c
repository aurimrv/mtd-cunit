Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
UTRAP_ON_STAT();@

 num_processes++;
 return proc;
}