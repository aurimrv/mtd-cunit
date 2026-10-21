char unget_char(char ch, character_stream fp)
{ char c;
  @
 (c = ungetc(TRAP_ON_POSITIVE(ch) , fp)) ;@

  if(c ==(-1))
    {
     return(c);
    }
  else
     return(c);
}