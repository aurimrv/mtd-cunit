#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void invert(int a[], int N);

static void run_invert_test(void)
{
    cunit_csv_load("test_cases_invert.csv");
    /* LLM_BODY_BEGIN */
        int i, N;
        int arr[100];
        extern int exists[100];

        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            const char *a_cell = cunit_csv_cell_by_name(active_row, "a");
            const char *N_cell = cunit_csv_cell_by_name(active_row, "N");
            int count = 0;
            const char *p = a_cell;

            sscanf(N_cell, "%d", &N);

            while (*p != '\0' && count < 100) {
                int val, consumed;
                if (sscanf(p, "%d%n", &val, &consumed) == 1) {
                    arr[count++] = val;
                    p += consumed;
                    while (*p != '\0' && *p != ',') {
                        p++;
                    }
                    if (*p == ',') {
                        p++;
                    }
                } else {
                    break;
                }
            }

            for (i = 0; i < 100; i++) {
                exists[i] = 0;
            }

            cunit_capture_stdout_begin();
            invert(arr, N);
            cunit_capture_stdout_end();
            cunit_oracle_check_stdout();
        }
    /* LLM_BODY_END */
}

void register_invert(void)
{
    CU_add_test(cunit_suite, "invert", run_invert_test);
}
