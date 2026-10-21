Ele * new_ele(int new_num)
{
 Ele *ele;
 ele = (Ele *) malloc(sizeof(Ele));
 ele->next = ((void *)0);
 ele->prev = ((void *)0);
 @
 ((ele->priority) = new_num) ;@

 return ele;
}