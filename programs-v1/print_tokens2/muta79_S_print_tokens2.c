char unget_char(char ch, character_stream fp)
{ char c;
  @
 (c = ungetc('\0' , fp)) ;@

  if(c ==(-1))
    {
     return(c);
    }
  else
     return(c);
}