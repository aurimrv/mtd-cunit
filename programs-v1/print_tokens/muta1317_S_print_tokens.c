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
      {@
return(numeric_case(tstream_ptr,token_ptr,ch,
      token_str,token_ind));@
}
      return(((void *)0));
}