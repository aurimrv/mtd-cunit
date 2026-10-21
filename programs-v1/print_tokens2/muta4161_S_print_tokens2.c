int is_identifier(token str)
{
  int i=1;
  if ( ((*__ctype_b_loc ())[(int) ((*str))] & (unsigned short int) _ISalpha) )
     {
        while( *(str+i) !='\0' )
           {
            if@
( (((* __ctype_b_loc())[((int) (* (str + i))) ] & ((unsigned short int) _ISalpha) ) || ((* __ctype_b_loc())[((int) (* (str + i))) ] & ((unsigned short int) 0) )) )@

               i++;
            else
               return(0);
           }
     return(1);
     }
  else
     return(0);
}