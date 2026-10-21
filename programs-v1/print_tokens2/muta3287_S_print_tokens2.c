int is_eof_token(token tok)
{
  if@
( (__MAXCHAR__ == (- 1)) )@

      return(1);
  else
      return(0);
}