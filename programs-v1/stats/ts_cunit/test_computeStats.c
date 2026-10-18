#include "cunit_common.h"
#include "cunit_gcov.h"
#include <math.h>
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void computeStats(int numbers[], int size);

static void run_computeStats_test(void)
{
    cunit_csv_load("test_cases_computeStats.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        int nums[128] = {0};
        const char *numbers_cell = cunit_csv_cell_by_name(active_row, "numbers");
        const char *size_cell = cunit_csv_cell_by_name(active_row, "size");
        int size = 0;
        int idx = 0;
        const char *p = numbers_cell;
        while (*p && idx < 128) {
            int val = 0;
            int consumed = 0;
            if (sscanf(p, "%d%n", &val, &consumed) != 1) {
                break;
            }
            nums[idx++] = val;
            p += consumed;
            if (*p == ',') {
                p++;
            } else {
                break;
            }
        }
        sscanf(size_cell, "%d", &size);
        cunit_capture_stdout_begin();
        computeStats(nums, size);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
    }
    /* LLM_BODY_END */
}

void register_computeStats(void)
{
    CU_add_test(cunit_suite, "computeStats", run_computeStats_test);
}
