#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int findLast(int x[], int y, int size);

static void run_findLast_test(void)
{
    cunit_csv_load("test_cases_findLast.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *x_cell = cunit_csv_cell_by_name(active_row, "x");
        const char *y_cell = cunit_csv_cell_by_name(active_row, "y");
        const char *size_cell = cunit_csv_cell_by_name(active_row, "size");
        int x[256];
        int count = 0;
        int y = 0;
        int size = 0;
        const char *p = x_cell;
        int n = 0;
        while (count < 256 && sscanf(p, "%d%n", &x[count], &n) == 1) {
            count++;
            p += n;
            while (*p == ' ' || *p == '\t') p++;
            if (*p == ',') {
                p++;
                while (*p == ' ' || *p == '\t') p++;
            } else {
                break;
            }
        }
        sscanf(y_cell, "%d", &y);
        sscanf(size_cell, "%d", &size);
        int ret = findLast(x, y, size);
        char out[64];
        snprintf(out, sizeof(out), "%d", ret);
        cunit_oracle_check_output(out);
    }
    /* LLM_BODY_END */
}

void register_findLast(void)
{
    CU_add_test(cunit_suite, "findLast", run_findLast_test);
}
