#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int countPositive(int x[], int length);

static void run_countPositive_test(void)
{
    cunit_csv_load("test_cases_countPositive.csv");
    /* LLM_BODY_BEGIN */
    int length;
    int arr[256] = {0};
    int n;
    const char *xcell;
    const char *lenstr;
    const char *p;
    int count;
    char out[32];

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        lenstr = cunit_csv_cell_by_name(active_row, "length");
        length = 0;
        sscanf(lenstr, "%d", &length);

        xcell = cunit_csv_cell_by_name(active_row, "x");
        n = 0;
        p = xcell;
        while (*p != '\0' && n < 256) {
            sscanf(p, "%d", &arr[n]);
            n++;
            while (*p != '\0' && *p != ',') {
                p++;
            }
            if (*p == ',') {
                p++;
            }
        }

        count = countPositive(arr, length);
        snprintf(out, sizeof(out), "%d", count);
        cunit_oracle_check_output(out);
    }
    /* LLM_BODY_END */
}

void register_countPositive(void)
{
    CU_add_test(cunit_suite, "countPositive", run_countPositive_test);
}
