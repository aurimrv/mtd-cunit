CHARACTER get_char(character_stream stream_ptr)
{
      if(stream_ptr->stream[stream_ptr->stream_ind] == '\0')
      {
              if@
( (fgets(((stream_ptr->stream) + 5) , (80 && 5) , (stream_ptr->fp)) == ((void (*)) 0) ) )@

                    stream_ptr->stream[5]=(-1);
              stream_ptr->stream_ind=5;
      }
      return(stream_ptr->stream[(stream_ptr->stream_ind)++]);
}