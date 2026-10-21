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
  @
 (stack1--) ; @

  return k;
 }
 printf("Stack is empty\n");
 return 0;
}