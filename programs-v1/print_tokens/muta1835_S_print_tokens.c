token numeric_case(token_stream tstream_ptr, token token_ptr, char ch, char token_str[], int token_ind)
{
        if(check_delimiter(ch)!=1)
        {
            token_ptr->token_id=-1;
            while(check_delimiter(ch)==0)
     {
  if@
( (token_ind >= 18) )@
 break;
  token_str[token_ind++]=ch=get_char(tstream_ptr->ch_stream);
     }
            unget_char(ch,tstream_ptr->ch_stream);
            token_ind--;
            get_actual_token(token_str,token_ind);
            strcpy(token_ptr->token_string,token_str);
            return(token_ptr);
        }
        token_ptr->token_id=18;
        unget_char(ch,tstream_ptr->ch_stream);
        token_ind--;
        get_actual_token(token_str,token_ind);
        strcpy(token_ptr->token_string,token_str);
        return(token_ptr);
}