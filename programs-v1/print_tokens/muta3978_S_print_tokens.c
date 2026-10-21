int get_actual_token(char token_str[], int token_ind)
{
          int ind,start;
          for(ind=token_ind;ind>0 && ((*__ctype_b_loc ())[(int) ((token_str[ind-1]))] & (unsigned short int) _ISspace);--ind);
           token_str[ind]='\0';token_ind=ind;
          for(ind=0;ind<token_ind;++ind)
                if(!((*__ctype_b_loc ())[(int) ((token_str[ind]))] & (unsigned short int) _ISspace))
                      break;
          for(start=0;@
 (ind <= __MININT__) ;@
++start,++ind)
                token_str[start]=token_str[ind];
          return 0;
}