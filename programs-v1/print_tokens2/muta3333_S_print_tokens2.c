int is_comment(token ident)
{
  if@
( ((* ident) == 1) )@

     return(1);
  else
     return(0);
}