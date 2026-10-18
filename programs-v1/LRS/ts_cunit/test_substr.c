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

static void run_substr_test(void)
{
    cunit_csv_load("test_cases_substr.csv");
    /* LLM_BODY_BEGIN */
    const char *str_cell, *star_cell, *len_cell;
    int star, len;
    char *result;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        str_cell = cunit_csv_cell_by_name(active_row, "str");
        star_cell = cunit_csv_cell_by_name(active_row, "star");
        len_cell = cunit_csv_cell_by_name(active_row, "len");
        star = atoi(star_cell);
        len = atoi(len_cell);
        result = substr((char*)str_cell, star, len);
        cunit_oracle_check_output(result);
        free(result);
    }
    /* LLM_BODY_END */
}

void register_substr(void)
{
    CU_add_test(cunit_suite, "substr", run_substr_test);
}
