int is_empty(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return -1;
 }
 if @
( ((pq->head) == TRAP_ON_ZERO((pq->tail))) )@
 {
  init(pq);
  return 1;
 } else
  return 0;
}