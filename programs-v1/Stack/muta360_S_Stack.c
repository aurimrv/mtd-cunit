int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 if @
( (bottom) )@

  bottom->below = ((void *)0);
 size--;
 return b->data;
}