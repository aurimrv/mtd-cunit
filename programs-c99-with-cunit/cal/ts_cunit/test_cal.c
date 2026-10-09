#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int cal(int month1, int day1, int month2, int day2, int year);

static void run_cal_test(void)
{
    cunit_csv_load("test_cases_cal.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *cell;
        int month1 = 0, day1 = 0, month2 = 0, day2 = 0, year = 0;
        cell = cunit_csv_cell_by_name(active_row, "month1");
        sscanf(cell, "%d", &month1);
        cell = cunit_csv_cell_by_name(active_row, "day1");
        sscanf(cell, "%d", &day1);
        cell = cunit_csv_cell_by_name(active_row, "month2");
        sscanf(cell, "%d", &month2);
        cell = cunit_csv_cell_by_name(active_row, "day2");
        sscanf(cell, "%d", &day2);
        cell = cunit_csv_cell_by_name(active_row, "year");
        sscanf(cell, "%d", &year);
        int result = cal(month1, day1, month2, day2, year);
        char output[32];
        snprintf(output, sizeof(output), "%d", result);
        cunit_oracle_check_output(output);
    }
    /* LLM_BODY_END */
}

void register_cal(void)
{
    CU_add_test(cunit_suite, "cal", run_cal_test);
}
