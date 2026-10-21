int constant(int state, char token_str[], int token_ind)
{
     switch(state)
     {
         case 27 : return(27);
         case 29 : @
 (token_str[(' ' - 2)] = ' ') ;@
 return(29);
         default : return(-1);
     }
}