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

static void run_keyword_test(void)
{
    cunit_csv_load("test_cases_keyword.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *state_str = cunit_csv_cell_by_name(active_row, "state");
        int state = atoi(state_str);
        cunit_capture_stdout_begin();
        if (state == 6 || state == 9 || state == 11 || state == 13 || state == 16) {
            int ret = keyword(state);
            cunit_capture_stdout_end();
            cunit_oracle_check_stdout();
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", ret);
            cunit_oracle_check_output(buf);
        } else {
            cunit_expect_exit();
            keyword(state);
        }
    }
    /* LLM_BODY_END */
}

void register_keyword(void)
{
    CU_add_test(cunit_suite, "keyword", run_keyword_test);
}
