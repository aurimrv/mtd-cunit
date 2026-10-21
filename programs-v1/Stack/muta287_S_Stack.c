int pop(void)
{
 int k;
 if (!isEmpty()) {
  k = top->data;
  @
 (top = (top->above)) ;@

  if (top != ((void *)0)) {
   free(top->above);
   top->above = ((void *)0);
  } else
   bottom = top;
  size--;
  return k;
 }
 printf("Stack is empty\n");
 return 0;
}