void upgrade_process_prio(int prio, float ratio)
{
 int count;
 int n;
 Ele *proc;
 List *src_queue, *dest_queue;
 if (prio >= 3)
  return;
 src_queue = prio_queue[prio];
 dest_queue = prio_queue[prio + 1];
 count = src_queue->mem_count;
 if (count > 0) {
  @
 (ratio = ((int) ((count * ratio) + 1)) ) ; @

  proc = find_nth(src_queue, n);
  if (proc) {
   src_queue = del_ele(src_queue, proc);
   proc->priority = prio;
   dest_queue = append_ele(dest_queue, proc);
  }
 }
}