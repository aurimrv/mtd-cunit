#include "cunit_common.h"
#include "cunit_gcov.h"
#include    <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int numZero(int arr[], int size);

static void run_numZero_test(void)
{
    cunit_csv_load("test_cases_numZero.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *arr_cell = cunit_csv_cell_by_name(active_row, "arr");
        const char *size_cell = cunit_csv_cell_by_name(active_row, "size");
        int size = 0;
        sscanf(size_cell, "%d", &size);
        int arr[20];
        int n = 0;
        const char *p = arr_cell;
        while (*p && n < 20) {
            int val, consumed;
            if (sscanf(p, "%d%n", &val, &consumed) != 1) break;
            arr[n++] = val;
            p += consumed;
            if (*p == ',') p++;
        }
        int ret = numZero(arr, size);
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%d", ret);
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_numZero(void)
{
    CU_add_test(cunit_suite, "numZero", run_numZero_test);
}
