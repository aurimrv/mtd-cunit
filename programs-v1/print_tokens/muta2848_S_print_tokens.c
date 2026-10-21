int skip(character_stream stream_ptr)
{
        char c;
        while((c=get_char(stream_ptr))!='\n' &&
               !is_end_of_character_stream(stream_ptr))
             ;
 if@
( ('\1' == (- 1)) )@
 unget_char(c, stream_ptr);
        return 0;
}