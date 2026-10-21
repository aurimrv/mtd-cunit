int is_str_constant(token str)
{
  int i=1;
  if ( *str =='"')
     { while (*(str+i)!='\0')
         { if(*(str+i)=='"')
             return(1);
           else
           i++;
         }
     @
UTRAP_ON_STAT();@

    }
  else
    return(0);
}