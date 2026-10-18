#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int lastZero(int x[], int length);

static void run_lastZero_test(void)
{
    cunit_csv_load("test_cases_lastZero.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *xcell;
        const char *len_cell;
        const char *p;
        int xarr[100];
        int xlen;
        int length;
        int ret;
        char buf[32];
        xcell = cunit_csv_cell_by_name(active_row, "x");
        len_cell = cunit_csv_cell_by_name(active_row, "length");
        xlen = 0;
        p = xcell;
        while (*p != '\0' && xlen < 100) {
            int sign = 1;
            int val = 0;
            int has_digit = 0;
            while (*p == ' ' || *p == '\t') {
                p++;
            }
            if (*p == '-') {
                sign = -1;
                p++;
            } else if (*p == '+') {
                p++;
            }
            while (*p >= '0' && *p <= '9') {
                val = val * 10 + (*p - '0');
                p++;
                has_digit = 1;
            }
            if (has_digit) {
                xarr[xlen] = sign * val;
                xlen++;
            }
            while (*p != '\0' && *p != ',') {
                p++;
            }
            if (*p == ',') {
                p++;
            }
        }
        length = 0;
        sscanf(len_cell, "%d", &length);
        ret = lastZero(xarr, length);
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_lastZero(void)
{
    CU_add_test(cunit_suite, "lastZero", run_lastZero_test);
}
