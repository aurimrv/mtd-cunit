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

static void run_sink_test(void)
{
    cunit_csv_load("test_cases_sink.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *pq_cell = cunit_csv_cell_by_name(active_row, "pq");
        const char *k_cell = cunit_csv_cell_by_name(active_row, "k");
        const char *N_cell = cunit_csv_cell_by_name(active_row, "N");
        char buf[1024];
        char *items[50];
        int n;
        char *tok;
        int k, N;
        strncpy(buf, pq_cell, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = 0;
        n = 0;
        tok = strtok(buf, ",");
        while (tok != NULL && n < 50) {
            items[n++] = tok;
            tok = strtok(NULL, ",");
        }
        sscanf(k_cell, "%d", &k);
        sscanf(N_cell, "%d", &N);
        sink(items, k, N);
    }
    /* LLM_BODY_END */
}

void register_sink(void)
{
    CU_add_test(cunit_suite, "sink", run_sink_test);
}
