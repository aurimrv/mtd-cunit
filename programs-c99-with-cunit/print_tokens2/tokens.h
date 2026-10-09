/* tokens.h code */

#include <stdio.h> 
#include "stream.h"
#define error 0
#define keyword 1
#define spec_symbol 2
#define identifier 3
#define num_constant 41
#define str_constant 42
#define char_constant 43
#define comment 5
#define end 6

typedef
    FILE *token_stream;
typedef   
    char *token;

token_stream open_token_stream(char *fname);
token get_token(token_stream tp);
void print_token(token tok);
int is_eof_token(token tok);
/* compare_token unused */

int is_token_end(int str_com_id, char ch);
int token_type(token tok);
int is_comment(token ident);
int is_keyword(token str);
int is_char_constant(token str);
int is_num_constant(token str);
int is_str_constant(token str);
int is_identifier(token str);
int is_spec_symbol(token str);
int unget_error(character_stream fp);
void print_spec_symbol(token str);

