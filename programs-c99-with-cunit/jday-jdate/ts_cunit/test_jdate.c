#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern long jday(int mon, int day, int year);
extern int *jdate(long j);

static void run_jdate_test(void)
{
    cunit_csv_load("test_cases_jdate.csv");
    /* LLM_BODY_BEGIN */
        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            long j;
            int *ret;
            char buffer[64];
            sscanf(cunit_csv_cell_by_name(active_row, "j"), "%ld", &j);
            ret = jdate(j);
            snprintf(buffer, sizeof(buffer), "%d,%d,%d,%d", ret[0], ret[1], ret[2], ret[3]);
            cunit_oracle_check_output(buffer);
        }
    /* LLM_BODY_END */
}

void register_jdate(void)
{
    CU_add_test(cunit_suite, "jdate", run_jdate_test);
}
