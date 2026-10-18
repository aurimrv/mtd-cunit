#include "cunit_common.h"
#include "cunit_gcov.h"
#include<stdio.h>
/* Project function prototypes (verified at seed time). */
extern void quicksort(int x[], int first, int last);

static void run_quicksort_test(void)
{
    cunit_csv_load("test_cases_quicksort.csv");
    /* LLM_BODY_BEGIN */
        int values[256];
        int n;
        int first;
        int last;
        const char *s;
        const char *firstStr;
        const char *lastStr;
        int sign;
        int val;
        char output[8192];
        int pos;
        int k;

        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            n = 0;
            s = cunit_csv_cell_by_name(active_row, "x");
            if (s != 0) {
                while (*s && n < 256) {
                    while (*s == ' ' || *s == '\t') s++;
                    if (*s == '\0') break;
                    sign = 1;
                    if (*s == '-') { sign = -1; s++; }
                    else if (*s == '+') { s++; }
                    val = 0;
                    while (*s >= '0' && *s <= '9') {
                        val = val * 10 + (*s - '0');
                        s++;
                    }
                    values[n++] = sign * val;
                    if (*s == ',') s++;
                }
            }
            firstStr = cunit_csv_cell_by_name(active_row, "first");
            lastStr = cunit_csv_cell_by_name(active_row, "last");
            first = 0;
            if (firstStr) {
                s = firstStr;
                sign = 1;
                if (*s == '-') { sign = -1; s++; }
                else if (*s == '+') { s++; }
                while (*s >= '0' && *s <= '9') {
                    first = first * 10 + (*s - '0');
                    s++;
                }
                first *= sign;
            }
            last = 0;
            if (lastStr) {
                s = lastStr;
                sign = 1;
                if (*s == '-') { sign = -1; s++; }
                else if (*s == '+') { s++; }
                while (*s >= '0' && *s <= '9') {
                    last = last * 10 + (*s - '0');
                    s++;
                }
                last *= sign;
            }
            quicksort(values, first, last);
            pos = 0;
            output[0] = '\0';
            for (k = 0; k < n; k++) {
                if (k > 0) {
                    output[pos++] = ',';
                    output[pos] = '\0';
                }
                pos += snprintf(output + pos, sizeof(output) - pos, "%d", values[k]);
            }
            cunit_oracle_check_output(output);
        }
    /* LLM_BODY_END */
}

void register_quicksort(void)
{
    CU_add_test(cunit_suite, "quicksort", run_quicksort_test);
}
