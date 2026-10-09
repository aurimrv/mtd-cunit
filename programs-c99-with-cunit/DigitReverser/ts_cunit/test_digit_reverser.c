#include "cunit_common.h"
#include "cunit_gcov.h"
#include    <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void digit_reverser(int N);

static void run_digit_reverser_test(void)
{
    cunit_csv_load("test_cases_digit_reverser.csv");
    /* LLM_BODY_BEGIN */
        int N;
        const char *cell;
        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            cell = cunit_csv_cell_by_name(active_row, "N");
            if (cell != NULL) {
                N = 0;
                sscanf(cell, "%d", &N);
            } else {
                N = 0;
            }
            cunit_capture_stdout_begin();
            digit_reverser(N);
            cunit_capture_stdout_end();
            cunit_oracle_check_stdout();
        }
    /* LLM_BODY_END */
}

void register_digit_reverser(void)
{
    CU_add_test(cunit_suite, "digit_reverser", run_digit_reverser_test);
}
