char *dequeue(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return ((void *)0);
 } else if @
(UTRAP_ON_TRUE(@
(is_empty(pq))@
))@
 {
  printf("Queue is empty\n");
  return ((void *)0);
 }
 return pq->names[(pq->head)++];
}