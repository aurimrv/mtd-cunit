#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int sum(int x[], int size);

static void run_sum_test(void)
{
    cunit_csv_load("test_cases_sum.csv");
    /* LLM_BODY_BEGIN */
    int n;
    int size;
    int result;
    int x[100];
    char buffer[64];
    const char *xcell;
    const char *sizecell;
    const char *p;
    int sign;
    int val;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        xcell = cunit_csv_cell_by_name(active_row, "x");
        sizecell = cunit_csv_cell_by_name(active_row, "size");
        size = 0;
        sscanf(sizecell, "%d", &size);

        n = 0;
        p = xcell;
        while (*p != '\0' && n < 100) {
            while (*p == ' ' || *p == ',') p++;
            if (*p == '\0') break;
            sign = 1;
            if (*p == '-') {
                sign = -1;
                p++;
            }
            val = 0;
            while (*p >= '0' && *p <= '9') {
                val = val * 10 + (*p - '0');
                p++;
            }
            x[n++] = sign * val;
        }
        while (n < 100) {
            x[n++] = 0;
        }

        result = sum(x, size);
        snprintf(buffer, sizeof(buffer), "%d", result);
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_sum(void)
{
    CU_add_test(cunit_suite, "sum", run_sum_test);
}
