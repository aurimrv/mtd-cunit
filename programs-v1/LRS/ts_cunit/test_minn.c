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

static void run_minn_test(void)
{
    cunit_csv_load("test_cases_minn.csv");
    /* LLM_BODY_BEGIN */
    int a, b, result;
    char buf[64];
    const char *a_str;
    const char *b_str;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        a_str = cunit_csv_cell_by_name(active_row, "a");
        b_str = cunit_csv_cell_by_name(active_row, "b");
        a = atoi(a_str);
        b = atoi(b_str);
        result = minn(a, b);
        snprintf(buf, sizeof(buf), "%d", result);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_minn(void)
{
    CU_add_test(cunit_suite, "minn", run_minn_test);
}
