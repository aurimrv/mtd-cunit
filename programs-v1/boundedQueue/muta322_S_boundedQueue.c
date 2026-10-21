void enqueue(BoundedQueue *q, int e)
{
 if (q->size == q->capacity) {
  @
return;@

 } else {
  q->size = q->size + 1;
  q->elements[q->back] = e;
  q->back = (q->back + 1) % q->capacity;
 }
}