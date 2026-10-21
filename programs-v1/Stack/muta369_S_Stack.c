int removeBottom(void)
{
 stack_link b = bottom;
 @
return b->data;@

 if (bottom != ((void *)0))
  bottom->below = ((void *)0);
 size--;
 return b->data;
}