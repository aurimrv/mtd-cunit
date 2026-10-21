int is_char_constant(token str)
{
  if @
( (((* str) == '#') && ((* __ctype_b_loc())[((int) 0) ] & ((unsigned short int) _ISalpha) )) )@

     return(1);
  else
     return(0);
}