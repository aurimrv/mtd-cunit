char *dequeue(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return ((void *)0);
 } else if (is_empty(pq)) {
  printf("Queue is empty\n");
  return ((void *)0);
 }
 @
return (pq->names)[((pq->tail)++)] ;@

}