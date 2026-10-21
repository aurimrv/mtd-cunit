BOOLEAN is_end_of_character_stream(character_stream stream_ptr)
{
      if@
( ((stream_ptr->stream)[(__MAXINT__ - 1)] == (- 1)) )@

            return(1);
      else
            return(0);
}