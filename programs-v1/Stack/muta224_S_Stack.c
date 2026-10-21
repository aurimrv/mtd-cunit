int pop(void)
{
 int k;
 if (!isEmpty()) {
  k = top->data;
  top = top->below;
  @
return 0;@
size--;
  return k;
 }
 printf("Stack is empty\n");
 return 0;
}