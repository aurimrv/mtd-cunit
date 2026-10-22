void init_prio_queue(int prio, int num_proc)
{
 List *queue;
 Ele *proc;
 int i;
 queue = new_list();
 for (i = 0; i < num_proc; i++) {
  proc = new_process(prio);
  queue = append_ele(queue, proc);
 }
 @
;@

}