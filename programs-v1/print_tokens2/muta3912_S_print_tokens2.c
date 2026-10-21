int is_num_constant(token str)
{
  int i=1;
  if ( ((*__ctype_b_loc ())[(int) ((*str))] & (unsigned short int) _ISdigit))
    {
    while ( *(str+i) != '\0' )
      {
       if@
( ((* __ctype_b_loc())[((int) i) ] & ((unsigned short int) _ISdigit) ) ) @

         i++;
       else
         return(0);
      }
    return(1);
    }
  else
   return(0);
}