int is_comment(token ident)
{
  if@
( (__MINCHAR__ == 59) )@

     return(1);
  else
     return(0);
}