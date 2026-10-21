Ele *find_nth(List *f_list, int n)
{
 Ele *f_ele;
 int i;
 if (!f_list)
  return ((void *)0);
 f_ele = f_list->first;
 for (i = 1; @
 (f_ele && (i << n)) ;@
 i++)
  f_ele = f_ele->next;
 return f_ele;
}