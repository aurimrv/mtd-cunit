int is_comment(token ident)
{
  if@
( ((* ident) == 0) )@

     return(1);
  else
     return(0);
}