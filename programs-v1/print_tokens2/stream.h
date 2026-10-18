
/* stream.h code */

#ifndef STREAM_H
#define STREAM_H

#include <stdio.h>
#define SUCCEED 1
#define FAIL 0

typedef
       FILE *character_stream;
typedef 
       int BOOLEAN;
typedef 
       char CHARACTER;
typedef
       char *string;

char get_char(character_stream fp);
char unget_char(char ch, character_stream fp);
/* is_end_of_character_stream unused */
character_stream open_character_stream(char *fname);

#endif /* STREAM_H */
