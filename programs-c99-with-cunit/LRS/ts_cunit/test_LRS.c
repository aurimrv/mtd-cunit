#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Source-local typedefs and constants (verified at seed time). */
#define MAX 100
/* Project function prototypes (verified at seed time). */
extern int minn(int a, int b);
extern void sort(char *a[], int sum);
extern char *substr(char *str, int star, int len);
extern char *lcp(char s[], char t[]);
extern char *LRS(char s[]);

static void run_LRS_test(void)
{
    cunit_csv_load("test_cases_LRS.csv");
    /* LLM_BODY_BEGIN */
    const char *s_cell;
    char *result;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        s_cell = cunit_csv_cell_by_name(active_row, "s");
        result = LRS((char*)s_cell);
        cunit_oracle_check_output(result);
    }
    /* LLM_BODY_END */
}

void register_LRS(void)
{
    CU_add_test(cunit_suite, "LRS", run_LRS_test);
}
