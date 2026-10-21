int dequeue(BoundedQueue *q)
{
 int r;
 if (q->size == 0) {
  printf("Queue is already empty!\n");
  return -1;
 } else {
  q->size = q->size - 1;
  @
 (r = (q->elements)[(r % (q->capacity))]) ; @

  q->front = (q->front + 1) % q->capacity;
  return r;
 }
}