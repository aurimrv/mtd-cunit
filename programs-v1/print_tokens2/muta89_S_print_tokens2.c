char unget_char(char ch, character_stream fp)
{ char c;
  c=ungetc(ch,fp);
  if(c ==(-1))
    {
     @
return ('\0') ;@

    }
  else
     return(c);
}