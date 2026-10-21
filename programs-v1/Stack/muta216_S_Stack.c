int pop(void)
{
 int k;
 if (!isEmpty()) {
  k = top->data;
  top = top->below;
  if (top != ((void *)0)) {
   @
return 0;@

   top->above = ((void *)0);
  } else
   bottom = top;
  size--;
  return k;
 }
 printf("Stack is empty\n");
 return 0;
}