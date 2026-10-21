int is_eof_token(token tok)
{
  if@
( (__MINCHAR__ == (- 1)) )@

      return(1);
  else
      return(0);
}