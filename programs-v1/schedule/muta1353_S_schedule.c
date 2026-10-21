Ele * new_process(int prio)
{
 Ele *proc;
 @
 (proc = new_ele((num_processes++))) ; @

 proc->priority = prio;
 num_processes++;
 return proc;
}