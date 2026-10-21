int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 if @
(UTRAP_ON_FALSE(@
(bottom != ((void *)0))@
))@

  bottom->below = ((void *)0);
 size--;
 return b->data;
}