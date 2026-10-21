BoundedQueue *createQueue(int maxElements)
{
 BoundedQueue *q;
 if (maxElements < 0) {
  printf("Invalid size.\n");
  q = 0;
  return q;
 }
 q = (BoundedQueue *) malloc(sizeof(BoundedQueue));
 q->elements = (int *)malloc(sizeof(int) * maxElements);
 @
 ((q->size) /= 0) ;@

 q->capacity = maxElements;
 q->front = 0;
 q->back = 0;
 return q;
}