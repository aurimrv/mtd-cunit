Ele * new_process(int prio)
{
 Ele *proc;
 @
UTRAP_ON_STAT();@

 proc->priority = prio;
 num_processes++;
 return proc;
}