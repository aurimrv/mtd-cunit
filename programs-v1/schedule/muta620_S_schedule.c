void schedule(void)
{
 int i;
 cur_proc = ((void *)0);
 for (i = 3; i > 0; i--) {
  if (prio_queue[i]->mem_count > 0) {
   @
 (cur_proc = (prio_queue[SUCC(i)]->first)) ;@

   prio_queue[i] = del_ele(prio_queue[i], cur_proc);
   return;
  }
 }
}