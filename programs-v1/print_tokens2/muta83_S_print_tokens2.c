char unget_char(char ch, character_stream fp)
{ char c;
  @
 (c = ungetc(__MINCHAR__ , fp)) ;@

  if(c ==(-1))
    {
     return(c);
    }
  else
     return(c);
}