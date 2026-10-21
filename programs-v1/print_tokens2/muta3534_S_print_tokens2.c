int is_char_constant(token str)
{
  if @
( (((* str) == '#') && ((* __ctype_b_loc())[((int) (* (str + 1))) ] & ((unsigned short int) 0) )) )@

     return(1);
  else
     return(0);
}