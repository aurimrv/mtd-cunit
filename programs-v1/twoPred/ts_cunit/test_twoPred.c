#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern char twoPred(int x, int y);

static void run_twoPred_test(void)
{
    cunit_csv_load("test_cases_twoPred.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *sx = cunit_csv_cell_by_name(active_row, "x");
        const char *sy = cunit_csv_cell_by_name(active_row, "y");
        int x = 0;
        int y = 0;
        char actual = 0;
        char buffer[32];
        sscanf(sx, "%d", &x);
        sscanf(sy, "%d", &y);
        actual = twoPred(x, y);
        snprintf(buffer, sizeof(buffer), "%c", actual);
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_twoPred(void)
{
    CU_add_test(cunit_suite, "twoPred", run_twoPred_test);
}
