void unblock_process(float ratio)
{
 int count;
 int n;
 Ele *proc;
 int prio;
 if (block_queue) {
  count = block_queue->mem_count;
  n = (int)(count * ratio + 1);
  proc = find_nth(block_queue, n);
  @
return;@
}
}