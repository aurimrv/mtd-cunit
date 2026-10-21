character_stream open_character_stream(string FILENAME)
{
      character_stream stream_ptr;
      stream_ptr=(character_stream)malloc(sizeof(struct stream_type));
      stream_ptr->stream_ind=5;
      stream_ptr->stream[5]='\0';
      if(FILENAME == ((void *)0))
          stream_ptr->fp=stdin;
      else @
return(stream_ptr);@
return(stream_ptr);
}