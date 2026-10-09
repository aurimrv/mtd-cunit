/* ***************************************************************
    File name : stream.h
    PURPOSE   : This is the header file for stream.c . This inlcudes
                the type definitions which are to be exported to the
                other routines.
  * **************************************************************** */

#ifndef STREAM_H
#define STREAM_H

typedef struct stream_type {
                               FILE *fp;  /* File pointer to stream */
                               int  stream_ind; /* buffer index */
                               char stream[80];  /* buffer for the file*/
                            } *character_stream;

typedef char CHARACTER;

character_stream open_character_stream(string FILENAME);

CHARACTER get_char(character_stream stream_ptr);

BOOLEAN is_end_of_character_stream(character_stream stream_ptr);

#endif /* STREAM_H */
