#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int power(int left, int right);

static void run_power_test(void)
{
    cunit_csv_load("test_cases_power.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *left_cell = cunit_csv_cell_by_name(active_row, "left");
        const char *right_cell = cunit_csv_cell_by_name(active_row, "right");
        int left = 0;
        int right = 0;
        if (left_cell) {
            sscanf(left_cell, "%d", &left);
        }
        if (right_cell) {
            sscanf(right_cell, "%d", &right);
        }
        int result = power(left, right);
        char buf[64];
        snprintf(buf, sizeof(buf), "%d", result);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_power(void)
{
    CU_add_test(cunit_suite, "power", run_power_test);
}
