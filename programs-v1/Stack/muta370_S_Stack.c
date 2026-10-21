int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 if (bottom != ((void *)0))
  @
return b->data;@

 size--;
 return b->data;
}