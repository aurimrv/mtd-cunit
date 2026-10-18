#include "cunit_common.h"
#include "cunit_gcov.h"
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define TRUE  1
# define FALSE 0
typedef int BOOLEAN;
typedef char *string;
#include "tokens.h"
/* Source-local typedefs and constants (verified at seed time). */
#define START 5
/* Project function prototypes (verified at seed time). */
extern character_stream open_character_stream(string FILENAME);
extern CHARACTER get_char(character_stream stream_ptr);
extern BOOLEAN is_end_of_character_stream(character_stream stream_ptr);
extern int unget_char(CHARACTER ch, character_stream stream_ptr);
extern token_stream open_token_stream(string FILENAME);
extern token get_token(token_stream tstream_ptr);
extern token numeric_case(token_stream tstream_ptr, token token_ptr, char ch, char token_str[], int token_ind);
extern token error_or_eof_case(token_stream tstream_ptr, token token_ptr, int cu_state, char token_str[], int token_ind, char ch);
extern int check_delimiter(char ch);
extern int keyword(int state);
extern int special(int state);
extern int skip(character_stream stream_ptr);
extern int constant(int state, char token_str[], int token_ind);
extern int next_state(int state, char ch);
extern BOOLEAN is_eof_token(token t);
extern BOOLEAN print_token(token token_ptr);
extern int get_actual_token(char token_str[], int token_ind);

static void run_print_token_test(void)
{
    cunit_csv_load("test_cases_print_token.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *cell = cunit_csv_cell_by_name(active_row, "token_ptr");
        struct token_type tok;
        tok.token_id = 0;
        tok.token_string[0] = '\0';
        const char *sep = strchr(cell, '|');
        if (sep != NULL) {
            size_t len = (size_t)(sep - cell);
            char idbuf[32];
            if (len >= sizeof(idbuf)) len = sizeof(idbuf) - 1;
            memcpy(idbuf, cell, len);
            idbuf[len] = '\0';
            tok.token_id = atoi(idbuf);
            strncpy(tok.token_string, sep + 1, sizeof(tok.token_string) - 1);
            tok.token_string[sizeof(tok.token_string) - 1] = '\0';
        } else {
            tok.token_id = atoi(cell);
        }
        cunit_capture_stdout_begin();
        int ret = print_token(&tok);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
        char outbuf[32];
        snprintf(outbuf, sizeof(outbuf), "%d", ret);
        cunit_oracle_check_output(outbuf);
    }
    /* LLM_BODY_END */
}

void register_print_token(void)
{
    CU_add_test(cunit_suite, "print_token", run_print_token_test);
}
