#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int FnNegate(int a);
extern int FnMinus(int a, int b);
extern int DifferentSigns(int a, int b);
extern int abss(int a);
extern int FnTimes(int a, int b);
extern int DefineAndRoundFraction(int a, int b);
extern int FnDivide(int a, int b);

static void run_FnNegate_test(void)
{
    cunit_csv_load("test_cases_FnNegate.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *a_str = cunit_csv_cell_by_name(active_row, "a");
        int a = 0;
        sscanf(a_str, "%d", &a);
        int result = FnNegate(a);
        char buf[64];
        snprintf(buf, sizeof(buf), "%d", result);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_FnNegate(void)
{
    CU_add_test(cunit_suite, "FnNegate", run_FnNegate_test);
}
