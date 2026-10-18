#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <string.h>
/* Project function prototypes (verified at seed time). */
extern int less01(char *pq[], int i, int j);
extern void exch(char *pq[], int i, int j);
extern int less02(char *v, char *w);
extern void sink(char *pq[], int k, int N);
extern void sort(char *pq[], int length);
extern int isSorted(char *a[], int length);
extern void show(char *a[], int length);

static void run_less02_test(void)
{
    cunit_csv_load("test_cases_less02.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *v_cell = cunit_csv_cell_by_name(active_row, "v");
        const char *w_cell = cunit_csv_cell_by_name(active_row, "w");
        char v[256];
        char w[256];
        int ret;
        char out[32];
        strncpy(v, v_cell, sizeof(v) - 1);
        v[sizeof(v) - 1] = 0;
        strncpy(w, w_cell, sizeof(w) - 1);
        w[sizeof(w) - 1] = 0;
        ret = less02(v, w);
        snprintf(out, sizeof(out), "%d", ret);
        cunit_oracle_check_output(out);
    }
    /* LLM_BODY_END */
}

void register_less02(void)
{
    CU_add_test(cunit_suite, "less02", run_less02_test);
}
