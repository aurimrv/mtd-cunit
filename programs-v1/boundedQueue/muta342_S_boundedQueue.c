void enqueue(BoundedQueue *q, int e)
{
 if (q->size == q->capacity) {
  printf("Queue is Full\n");
 } else {
  @
UTRAP_ON_STAT();@

  q->elements[q->back] = e;
  q->back = (q->back + 1) % q->capacity;
 }
}