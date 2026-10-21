int is_comment(token ident)
{
  if@
( (TRAP_ON_POSITIVE((* ident)) == 59) )@

     return(1);
  else
     return(0);
}