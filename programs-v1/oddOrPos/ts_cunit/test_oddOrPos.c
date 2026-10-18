#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int oddOrPos(int x[], int length);

static void run_oddOrPos_test(void)
{
    cunit_csv_load("test_cases_oddOrPos.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *xcell = cunit_csv_cell_by_name(active_row, "x");
        const char *lencell = cunit_csv_cell_by_name(active_row, "length");
        int length = 0;
        int x[128];
        int n = 0;
        const char *p = xcell;

        sscanf(lencell, "%d", &length);

        while (*p != '\0' && n < 128) {
            int val = 0;
            int adv = 0;
            if (sscanf(p, "%d%n", &val, &adv) != 1) {
                break;
            }
            x[n] = val;
            n++;
            p += adv;
            while (*p == ',' || *p == ' ' || *p == '\t') {
                p++;
            }
        }

        int actual = oddOrPos(x, length);
        char buf[64];
        snprintf(buf, sizeof(buf), "%d", actual);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_oddOrPos(void)
{
    CU_add_test(cunit_suite, "oddOrPos", run_oddOrPos_test);
}
