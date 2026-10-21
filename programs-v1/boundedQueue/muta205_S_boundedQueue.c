void enqueue(BoundedQueue *q, int e)
{
 if (q->size == q->capacity) {
  printf("Queue is Full\n");
 } else {
  q->size = q->size + 1;
  q->elements[q->back] = e;
  @
 ((q->back) = ((0 + 1) % (q->capacity))) ;@

 }
}