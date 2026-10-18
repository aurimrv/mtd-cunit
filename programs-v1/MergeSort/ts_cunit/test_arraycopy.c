#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void arraycopy(int *src, int srcstart, int *dest, int deststart, int length);
extern void mergeSort(int *list, int len);
extern void merge(int *list1, int list1len, int *list2, int list2len, int *temp);

static void run_arraycopy_test(void)
{
    cunit_csv_load("test_cases_arraycopy.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *src_str = cunit_csv_cell_by_name(active_row, "src");
        int src[100];
        int src_count = 0;
        const char *p = src_str;
        while (*p && src_count < 100) {
            int val, n;
            if (sscanf(p, "%d%n", &val, &n) == 1) {
                src[src_count++] = val;
                p += n;
                if (*p == ',') p++;
            } else break;
        }
        const char *dest_str = cunit_csv_cell_by_name(active_row, "dest");
        int dest[100];
        int dest_count = 0;
        p = dest_str;
        while (*p && dest_count < 100) {
            int val, n;
            if (sscanf(p, "%d%n", &val, &n) == 1) {
                dest[dest_count++] = val;
                p += n;
                if (*p == ',') p++;
            } else break;
        }
        int srcstart; sscanf(cunit_csv_cell_by_name(active_row, "srcstart"), "%d", &srcstart);
        int deststart; sscanf(cunit_csv_cell_by_name(active_row, "deststart"), "%d", &deststart);
        int length; sscanf(cunit_csv_cell_by_name(active_row, "length"), "%d", &length);
        arraycopy(src, srcstart, dest, deststart, length);
        cunit_oracle_check_output("");
    }
    /* LLM_BODY_END */
}

void register_arraycopy(void)
{
    CU_add_test(cunit_suite, "arraycopy", run_arraycopy_test);
}
