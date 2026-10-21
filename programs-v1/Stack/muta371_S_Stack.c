int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 @
return b->data;@
size--;
 return b->data;
}