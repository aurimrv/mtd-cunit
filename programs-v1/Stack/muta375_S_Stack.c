int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 @
;@
size--;
 return b->data;
}