int skip(character_stream stream_ptr)
{
        char c;
        while@
( ('\n' && (! is_end_of_character_stream(stream_ptr))) )@

             ;
 if(c==(-1)) unget_char(c, stream_ptr);
        return 0;
}