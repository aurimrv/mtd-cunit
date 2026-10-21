int is_comment(token ident)
{
  if@
( (TRAP_ON_ZERO((* ident)) == 59) )@

     return(1);
  else
     return(0);
}