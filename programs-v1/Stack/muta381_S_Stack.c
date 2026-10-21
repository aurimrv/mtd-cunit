int removeBottom(void)
{
 stack_link b = bottom;
 @
UTRAP_ON_STAT();@

 if (bottom != ((void *)0))
  bottom->below = ((void *)0);
 size--;
 return b->data;
}