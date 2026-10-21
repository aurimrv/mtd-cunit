int skip(character_stream stream_ptr)
{
        char c;
        @
UTRAP_ON_STAT();@
if(c==(-1)) unget_char(c, stream_ptr);
        return 0;
}