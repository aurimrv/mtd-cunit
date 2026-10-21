CHARACTER get_char(character_stream stream_ptr)
{
      @
UTRAP_ON_STAT();@
return(stream_ptr->stream[(stream_ptr->stream_ind)++]);
}