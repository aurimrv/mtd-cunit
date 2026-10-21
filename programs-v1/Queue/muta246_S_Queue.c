void enqueue(QUEUE *pq, char *p)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return;
 } else if (is_full(pq)) {
  printf("Queue is full\n");
  return;
 }
 @
 (strcpy((pq->names)[(++ (pq->tail))] , p)) ;@

 printf("\n\n\t\t Element Successfully Inserted");
}