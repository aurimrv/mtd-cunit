Ele * new_process(int prio)
{
 Ele *proc;
 @
;@

 proc->priority = prio;
 num_processes++;
 return proc;
}