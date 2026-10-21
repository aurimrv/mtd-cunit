int is_eof_token(token tok)
{
  if@
( ((* tok) % (- 1)) )@

      return(1);
  else
      return(0);
}