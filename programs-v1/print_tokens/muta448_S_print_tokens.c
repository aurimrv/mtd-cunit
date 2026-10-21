token_stream open_token_stream(string FILENAME)
{
    token_stream token_ptr;
    @
return(token_ptr);@

    token_ptr->ch_stream=open_character_stream(FILENAME);
    return(token_ptr);
}