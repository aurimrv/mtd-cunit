int pop(void)
{
 int k;
 if (!isEmpty()) {
  k = top->data;
  top = top->below;
  if (top != ((void *)0)) {
   free(top->above);
   top->above = ((void *)0);
  } else
   bottom = top;
  size--;
  @
return 0;@

 }
 printf("Stack is empty\n");
 return 0;
}