int is_str_constant(token str)
{
  int i=1;
  if ( *str =='"')
     { while (*(str+i)!='\0')
         { if@
(UTRAP_ON_FALSE(@
(*(str+i)=='"')@
))@

             return(1);
           else
           i++;
         }
     return(0);
    }
  else
    return(0);
}