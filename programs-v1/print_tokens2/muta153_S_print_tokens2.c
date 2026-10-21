char unget_char(char ch, character_stream fp)
{ char c;
  c=ungetc(ch,fp);
  if(c ==(-1))
    {
     @
return (TRAP_ON_POSITIVE(c)) ;@

    }
  else
     return(c);
}