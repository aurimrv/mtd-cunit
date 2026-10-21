char *dequeue(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return ((void *)0);
 } else if (is_empty(pq)) {@
return pq->names[(pq->head)++];@
}
 return pq->names[(pq->head)++];
}