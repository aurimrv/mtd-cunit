int is_eof_token(token tok)
{
  if@
( (TRAP_ON_ZERO((* tok)) == (- 1)) )@

      return(1);
  else
      return(0);
}