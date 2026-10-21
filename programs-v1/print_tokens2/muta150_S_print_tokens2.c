char unget_char(char ch, character_stream fp)
{ char c;
  c=ungetc(ch,fp);
  if@
( (TRAP_ON_POSITIVE(c) == (- 1)) )@

    {
     return(c);
    }
  else
     return(c);
}