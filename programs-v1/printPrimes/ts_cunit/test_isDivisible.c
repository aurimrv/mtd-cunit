#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int isDivisible(int i, int j);
extern void printPrimes(int n);

static void run_isDivisible_test(void)
{
    cunit_csv_load("test_cases_isDivisible.csv");
    /* LLM_BODY_BEGIN */
    int i, j;
    char buf[64];
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        sscanf(cunit_csv_cell_by_name(active_row, "i"), "%d", &i);
        sscanf(cunit_csv_cell_by_name(active_row, "j"), "%d", &j);
        snprintf(buf, sizeof(buf), "%d", isDivisible(i, j));
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_isDivisible(void)
{
    CU_add_test(cunit_suite, "isDivisible", run_isDivisible_test);
}
