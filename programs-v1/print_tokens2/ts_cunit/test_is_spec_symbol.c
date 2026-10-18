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

static void run_is_spec_symbol_test(void)
{
    cunit_csv_load("test_cases_is_spec_symbol.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        char *str = (char *)cunit_csv_cell_by_name(active_row, "str");
        int result = is_spec_symbol(str);
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%d", result);
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_is_spec_symbol(void)
{
    CU_add_test(cunit_suite, "is_spec_symbol", run_is_spec_symbol_test);
}
