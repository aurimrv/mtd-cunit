Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 @
;@

 num_processes++;
 return proc;
}