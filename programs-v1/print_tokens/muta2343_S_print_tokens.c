int check_delimiter(char ch)
{
      if@
( ((! (_ISdigit & ((unsigned short int) _ISalpha) )) && (! ((* __ctype_b_loc())[((int) ch) ] & ((unsigned short int) _ISdigit) ))) )@

          return(1);
      return(0);
}