char unget_char(char ch, character_stream fp)
{ char c;
  @
 (ch = ungetc(ch , fp)) ; @

  if(c ==(-1))
    {
     return(c);
    }
  else
     return(c);
}