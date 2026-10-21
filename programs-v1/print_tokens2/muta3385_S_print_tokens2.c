int is_comment(token ident)
{
  if@
( (TRAP_ON_NEGATIVE((* ident)) == 59) )@

     return(1);
  else
     return(0);
}