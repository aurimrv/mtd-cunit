int is_empty(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return -1;
 }
 if @
(UTRAP_ON_FALSE(@
(pq->head == pq->tail)@
))@
 {
  init(pq);
  return 1;
 } else
  return 0;
}