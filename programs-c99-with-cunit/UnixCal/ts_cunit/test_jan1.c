#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
/* Project function prototypes (verified at seed time). */
extern void dispatch(int argc, char *argv[]);
extern void pstr(char *str, int n);
extern void cal(int m, int y, char *p, int w);
extern int jan1(int yr);

static void run_jan1_test(void)
{
    cunit_csv_load("test_cases_jan1.csv");
    /* LLM_BODY_BEGIN */
        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            const char *yr_cell = cunit_csv_cell_by_name(active_row, "yr");
            int yr = atoi(yr_cell);
            int result = jan1(yr);
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", result);
            cunit_oracle_check_output(buf);
        }
    /* LLM_BODY_END */
}

void register_jan1(void)
{
    CU_add_test(cunit_suite, "jan1", run_jan1_test);
}
