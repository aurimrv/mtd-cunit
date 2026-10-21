int removeBottom(void)
{
 stack_link b = bottom;
 bottom = bottom->above;
 @
UTRAP_ON_STAT();@
size--;
 return b->data;
}