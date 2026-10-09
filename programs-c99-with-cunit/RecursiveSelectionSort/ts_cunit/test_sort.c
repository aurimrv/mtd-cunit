#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
/* Project function prototypes (verified at seed time). */
extern void sort(double *list, int low, int high);

static void run_sort_test(void)
{
    cunit_csv_load("test_cases_sort.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *list_cell = cunit_csv_cell_by_name(active_row, "list");
        const char *low_cell = cunit_csv_cell_by_name(active_row, "low");
        const char *high_cell = cunit_csv_cell_by_name(active_row, "high");
        double arr[100];
        int n = 0;
        const char *p = list_cell;
        while (*p && n < 100) {
            char *end;
            arr[n++] = strtod(p, &end);
            if (*end == ',') {
                p = end + 1;
            } else {
                break;
            }
        }
        int low = atoi(low_cell);
        int high = atoi(high_cell);
        sort(arr, low, high);
        char buf[4096];
        size_t pos = 0;
        int i;
        for (i = 0; i < n; i++) {
            int written;
            if (i > 0) {
                buf[pos++] = ',';
            }
            written = snprintf(buf + pos, sizeof(buf) - pos, "%.2f", arr[i]);
            if (written > 0) {
                pos += (size_t)written;
            }
        }
        buf[pos] = '\0';
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_sort(void)
{
    CU_add_test(cunit_suite, "sort", run_sort_test);
}
