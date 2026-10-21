List *append_ele(List *a_list, Ele *a_ele)
{
 if (!a_list)
  a_list = new_list();
 a_ele->prev = a_list->last;
 if (a_list->last)
  a_list->last->next = a_ele;
 else
  @
return (a_list);@

 a_list->last = a_ele;
 a_ele->next = ((void *)0);
 a_list->mem_count++;
 return (a_list);
}