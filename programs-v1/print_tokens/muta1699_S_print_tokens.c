token get_token(token_stream tstream_ptr)
{
      char token_str[80];
      int token_ind;
      token token_ptr;
      CHARACTER ch;
      int cu_state,next_st,token_found;
      token_ptr=(token)(malloc(sizeof(struct token_type)));
      ch=get_char(tstream_ptr->ch_stream);
      cu_state=token_ind=token_found=0;
      while(!token_found)
      {
   if(token_ind < 80)
   {
       token_str[token_ind++]=ch;
       next_st=next_state(cu_state,ch);
   }
   else
   {
       next_st = -1;
   }
   if (next_st == -1) {
       return(error_or_eof_case(tstream_ptr,
           token_ptr,cu_state,token_str,token_ind,ch));
   } else if (next_st == -2) {
       return(numeric_case(tstream_ptr,token_ptr,ch,
      token_str,token_ind));
   } else if (next_st == -3) {
       token_ptr->token_id=17;
       unget_char(ch,tstream_ptr->ch_stream);
       token_ind--;
       get_actual_token(token_str,token_ind);
       strcpy(token_ptr->token_string,token_str);
       return(token_ptr);
   }
   switch(next_st)
            {
                 default : break;
                 case 6 :
                 case 9 :
                 case 11 :
                 case 13 :
                 case 16 : ch=get_char(tstream_ptr->ch_stream);
                           if(check_delimiter(ch)==1)
                           {
                                 token_ptr->token_id=keyword(next_st);
                                 @
 (unget_char(tstream_ptr , (tstream_ptr->ch_stream))) ; @

                                 token_ptr->token_string[0]='\0';
                                 return(token_ptr);
                           }
                           unget_char(ch,tstream_ptr->ch_stream);
                           break;
                 case 19 :
                 case 20 :
                 case 21 :
                 case 22 :
                 case 23 :
                 case 24 :
                 case 25 :
                 case 32 : token_ptr->token_id=special(next_st);
                           token_ptr->token_string[0]='\0';
                           return(token_ptr);
                 case 27 :
                 case 29 : token_ptr->token_id=constant(next_st,token_str,token_ind);
                           get_actual_token(token_str,token_ind);
                           strcpy(token_ptr->token_string,token_str);
                           return(token_ptr);
                 case 30 :
                           skip(tstream_ptr->ch_stream);
                           token_ind=next_st=0;
                           break;
            }
            cu_state=next_st;
            ch=get_char(tstream_ptr->ch_stream);
      }
      return(((void *)0));
}