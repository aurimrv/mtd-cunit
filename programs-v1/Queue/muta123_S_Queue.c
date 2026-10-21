int is_full(QUEUE *pq)
{
 if (pq == ((void *)0)) {
  printf("Invalid Queue\n");
  return -1;
 }
 @
return (TRAP_ON_ZERO((pq->tail)) == 10) ;@

}