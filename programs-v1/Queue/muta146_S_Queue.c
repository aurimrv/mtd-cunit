int is_empty(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return -1;
 }
 if @
( ((pq->head) == __MININT__) )@
 {
  init(pq);
  return 1;
 } else
  return 0;
}