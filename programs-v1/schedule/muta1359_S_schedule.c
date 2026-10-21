Ele * new_process(int prio)
{
 Ele *proc;
 @
 (proc = new_ele((prio++))) ; @

 proc->priority = prio;
 num_processes++;
 return proc;
}