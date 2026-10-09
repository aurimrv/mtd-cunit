#include "cunit_common.h"
#include "cunit_gcov.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
/* Source-local typedefs and constants (verified at seed time). */
#define TRUE 1
#define FALSE 0
/* Project function prototypes (verified at seed time). */
extern character_stream open_character_stream(char *fname);
extern char get_char(character_stream fp);
extern char unget_char(char ch, character_stream fp);
extern token_stream open_token_stream(char *fname);
extern token get_token(token_stream tp);
extern int is_token_end(int str_com_id, char ch);
extern int token_type(token tok);
extern void print_token(token tok);
extern int is_eof_token(token tok);
extern int is_comment(token ident);
extern int is_keyword(token str);
extern int is_char_constant(token str);
extern int is_num_constant(token str);
extern int is_str_constant(token str);
extern int is_identifier(token str);
extern int unget_error(character_stream fp);
extern void print_spec_symbol(token str);
extern int is_spec_symbol(token str);

static void run_open_token_stream_test(void)
{
    cunit_csv_load("test_cases_open_token_stream.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *tn = cunit_csv_cell_by_name(active_row, "test_number");
        const char *fname_cell = cunit_csv_cell_by_name(active_row, "fname");
        char *fname = (char *)fname_cell;
        if (tn[0] == '2') {
            cunit_expect_exit();
            open_token_stream(fname);
        } else {
            token_stream ts = open_token_stream(fname);
            char buf[32];
            if (ts == NULL) {
                snprintf(buf, sizeof(buf), "NULL");
            } else {
                snprintf(buf, sizeof(buf), "NONNULL");
            }
            cunit_oracle_check_output(buf);
        }
    }
    /* LLM_BODY_END */
}

void register_open_token_stream(void)
{
    CU_add_test(cunit_suite, "open_token_stream", run_open_token_stream_test);
}
