#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <string.h>
/* Project function prototypes (verified at seed time). */
extern int isPalindrome(char s[]);

static void run_isPalindrome_test(void)
{
    cunit_csv_load("test_cases_isPalindrome.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *s_cell = cunit_csv_cell_by_name(active_row, "s");
        char s_buf[256];
        snprintf(s_buf, sizeof(s_buf), "%s", s_cell ? s_cell : "");
        int ret = isPalindrome(s_buf);
        char out[32];
        snprintf(out, sizeof(out), "%d", ret);
        cunit_oracle_check_output(out);
    }
    /* LLM_BODY_END */
}

void register_isPalindrome(void)
{
    CU_add_test(cunit_suite, "isPalindrome", run_isPalindrome_test);
}
