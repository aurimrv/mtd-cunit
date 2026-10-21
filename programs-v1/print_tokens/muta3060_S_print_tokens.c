int constant(int state, char token_str[], int token_ind)
{
     switch(state)
     {
         case 27 : @
UTRAP_ON_STAT();@

         case 29 : token_str[token_ind-2]=' '; return(29);
         default : return(-1);
     }
}