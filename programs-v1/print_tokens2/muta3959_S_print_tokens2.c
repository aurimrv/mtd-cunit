int is_str_constant(token str)
{
  int i=1;
  if @
( (0 == '"') )@

     { while (*(str+i)!='\0')
         { if(*(str+i)=='"')
             return(1);
           else
           i++;
         }
     return(0);
    }
  else
    return(0);
}