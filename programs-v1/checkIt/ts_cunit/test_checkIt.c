#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void checkIt(int a, int b, int c);

static void run_checkIt_test(void)
{
    cunit_csv_load("test_cases_checkIt.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        int a = 0;
        int b = 0;
        int c = 0;
        const char *sa = cunit_csv_cell_by_name(active_row, "a");
        const char *sb = cunit_csv_cell_by_name(active_row, "b");
        const char *sc = cunit_csv_cell_by_name(active_row, "c");
        if (sa != NULL) {
            sscanf(sa, "%d", &a);
        }
        if (sb != NULL) {
            sscanf(sb, "%d", &b);
        }
        if (sc != NULL) {
            sscanf(sc, "%d", &c);
        }
        cunit_capture_stdout_begin();
        checkIt(a, b, c);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
    }
    /* LLM_BODY_END */
}

void register_checkIt(void)
{
    CU_add_test(cunit_suite, "checkIt", run_checkIt_test);
}
