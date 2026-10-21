void display(QUEUE *pq)
{
 int i;
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return;
 }
 for (i = pq->head; @
 (SUCC(i) < (pq->tail)) ;@
 i++)
  printf("\n\t\t :%s", pq->names[i]);
 printf("\n");
}