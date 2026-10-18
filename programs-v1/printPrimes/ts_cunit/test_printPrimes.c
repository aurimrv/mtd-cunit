#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int isDivisible(int i, int j);
extern void printPrimes(int n);

static void run_printPrimes_test(void)
{
    cunit_csv_load("test_cases_printPrimes.csv");
    /* LLM_BODY_BEGIN */
    int n;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        sscanf(cunit_csv_cell_by_name(active_row, "n"), "%d", &n);
        cunit_capture_stdout_begin();
        printPrimes(n);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
    }
    /* LLM_BODY_END */
}

void register_printPrimes(void)
{
    CU_add_test(cunit_suite, "printPrimes", run_printPrimes_test);
}
