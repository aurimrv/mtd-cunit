void print_stack(void)
{
 stack_link b = bottom;
 printf("Bottom - up: ");
 while (b != ((void *)0)) {
  @
 (printf("%d " , stack1)) ; @

  b = b->above;
 }
 printf("\n");
}