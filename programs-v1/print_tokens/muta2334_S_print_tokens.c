int check_delimiter(char ch)
{
      if(!((*__ctype_b_loc ())[(int) ((ch))] & (unsigned short int) _ISalpha) && !((*__ctype_b_loc ())[(int) ((ch))] & (unsigned short int) _ISdigit))
          @
return (0) ;@

      return(0);
}