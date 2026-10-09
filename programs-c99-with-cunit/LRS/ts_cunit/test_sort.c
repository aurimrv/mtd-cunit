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

static void run_sort_test(void)
{
    cunit_csv_load("test_cases_sort.csv");
    /* LLM_BODY_BEGIN */
    int i, n, sum;
    char *a[50];
    char buf[1024];
    char out[1024];
    char *token;
    const char *a_cell;
    const char *sum_cell;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        a_cell = cunit_csv_cell_by_name(active_row, "a");
        sum_cell = cunit_csv_cell_by_name(active_row, "sum");
        sum = atoi(sum_cell);
        n = 0;
        strncpy(buf, a_cell, sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';
        token = strtok(buf, ",");
        while (token != NULL && n < 50) {
            a[n] = malloc(strlen(token)+1);
            strcpy(a[n], token);
            n++;
            token = strtok(NULL, ",");
        }
        sort(a, sum);
        out[0] = '\0';
        for (i = 0; i < sum; i++) {
            if (i > 0) strcat(out, ",");
            strcat(out, a[i]);
        }
        cunit_oracle_check_output(out);
        for (i = 0; i < n; i++) free(a[i]);
    }
    /* LLM_BODY_END */
}

void register_sort(void)
{
    CU_add_test(cunit_suite, "sort", run_sort_test);
}
