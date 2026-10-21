void display(QUEUE *pq)
{
 int i;
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return;
 }
 for (@
 (i = PRED((pq->head))) ;@
 i < pq->tail; i++)
  printf("\n\t\t :%s", pq->names[i]);
 printf("\n");
}