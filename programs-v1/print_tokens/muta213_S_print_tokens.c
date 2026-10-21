CHARACTER get_char(character_stream stream_ptr)
{
      if(stream_ptr->stream[stream_ptr->stream_ind] == '\0')
      {
              if@
( ((void (*)) 0)  )@

                    stream_ptr->stream[5]=(-1);
              stream_ptr->stream_ind=5;
      }
      return(stream_ptr->stream[(stream_ptr->stream_ind)++]);
}