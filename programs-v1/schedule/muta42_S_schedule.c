List *new_list(void)
{
 List *list;
 list = (List *) malloc(sizeof(List));
 list->first = ((void *)0);
 list->last = ((void *)0);
 @
 ((list->mem_count) /= 0) ;@

 return (list);
}