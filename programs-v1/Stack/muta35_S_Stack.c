void join(stack_link above, stack_link below)
{
 @
UTRAP_ON_STAT();@
if (above != ((void *)0))
  above->below = below;
}