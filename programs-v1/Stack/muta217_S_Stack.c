int pop(void)
{
 int k;
 if (!isEmpty()) {
  k = top->data;
  top = top->below;
  if (top != ((void *)0)) {
   free(top->above);
   @
return k;@

  } else
   bottom = top;
  size--;
  return k;
 }
 printf("Stack is empty\n");
 return 0;
}