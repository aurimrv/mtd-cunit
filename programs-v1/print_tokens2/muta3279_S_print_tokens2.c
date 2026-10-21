int is_eof_token(token tok)
{
  if@
( ((* tok) == (- 0)) )@

      return(1);
  else
      return(0);
}