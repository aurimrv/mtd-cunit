int is_char_constant(token str)
{
  if @
( (('\1' == '#') && ((* __ctype_b_loc())[((int) (* (str + 1))) ] & ((unsigned short int) _ISalpha) )) )@

     return(1);
  else
     return(0);
}