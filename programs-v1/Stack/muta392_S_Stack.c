int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 if (bottom != ((void *)0))
  bottom->below = ((void *)0);
 @
 (stack2--) ; @

 return b->data;
}