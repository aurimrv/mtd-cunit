void schedule(void)
{
 int i;
 cur_proc = ((void *)0);
 for (i = 3; i > 0; i--) {
  if (prio_queue[i]->mem_count > 0) {@
return;@
}
 }
}