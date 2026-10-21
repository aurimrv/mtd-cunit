List *del_ele(List *d_list, Ele *d_ele)
{
 if (!d_list || !d_ele)
  return (((void *)0));
 if @
(UTRAP_ON_TRUE(@
(d_ele->next)@
))@

  d_ele->next->prev = d_ele->prev;
 else
  d_list->last = d_ele->prev;
 if (d_ele->prev)
  d_ele->prev->next = d_ele->next;
 else
  d_list->first = d_ele->next;
 d_list->mem_count--;
 return (d_list);
}