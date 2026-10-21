CHARACTER get_char(character_stream stream_ptr)
{
      if(stream_ptr->stream[stream_ptr->stream_ind] == '\0')
      {
              @
return(stream_ptr->stream[(stream_ptr->stream_ind)++]);@
stream_ptr->stream_ind=5;
      }
      return(stream_ptr->stream[(stream_ptr->stream_ind)++]);
}