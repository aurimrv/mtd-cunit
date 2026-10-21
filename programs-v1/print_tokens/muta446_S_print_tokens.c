token_stream open_token_stream(string FILENAME)
{
    token_stream token_ptr;
    @
 (token_ptr += ((token_stream) malloc(sizeof(struct token_stream_type) )) ) ;@

    token_ptr->ch_stream=open_character_stream(FILENAME);
    return(token_ptr);
}