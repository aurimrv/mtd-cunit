BOOLEAN is_end_of_character_stream(character_stream stream_ptr)
{
      if@
(UTRAP_ON_FALSE(@
(stream_ptr->stream[stream_ptr->stream_ind-1] == (-1))@
))@

            return(1);
      else
            return(0);
}