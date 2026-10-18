#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern long jday(int mon, int day, int year);
extern int *jdate(long j);

static void run_jday_test(void)
{
    cunit_csv_load("test_cases_jday.csv");
    /* LLM_BODY_BEGIN */
        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            int mon, day, year;
            long result;
            char buffer[64];
            sscanf(cunit_csv_cell_by_name(active_row, "mon"), "%d", &mon);
            sscanf(cunit_csv_cell_by_name(active_row, "day"), "%d", &day);
            sscanf(cunit_csv_cell_by_name(active_row, "year"), "%d", &year);
            result = jday(mon, day, year);
            snprintf(buffer, sizeof(buffer), "%ld", result);
            cunit_oracle_check_output(buffer);
        }
    /* LLM_BODY_END */
}

void register_jday(void)
{
    CU_add_test(cunit_suite, "jday", run_jday_test);
}
