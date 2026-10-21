int is_char_constant(token str)
{
  if @
( (((* str) == '#') && (_ISalpha & ((unsigned short int) _ISalpha) )) )@

     return(1);
  else
     return(0);
}