int constant(int state, char token_str[], int token_ind)
{
     switch(state)
     {
         case 27 : return(27);
         @
goto __LABEL_MUTA__; @
case 29 :@
 UTRAP_ON_CASE(); @
@
__LABEL_MUTA__: ; @
 token_str[token_ind-2]=' '; return(29);
         default : return(-1);
     }
}