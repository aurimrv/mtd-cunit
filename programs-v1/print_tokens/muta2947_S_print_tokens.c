int skip(character_stream stream_ptr)
{
        char c;
        while((c=get_char(stream_ptr))!='\n' &&
               !is_end_of_character_stream(stream_ptr))
             ;
 if(c==(-1)) @
UTRAP_ON_STAT();@

        return 0;
}