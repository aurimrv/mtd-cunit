#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void arraycopy(int *src, int srcstart, int *dest, int deststart, int length);
extern void mergeSort(int *list, int len);
extern void merge(int *list1, int list1len, int *list2, int list2len, int *temp);

static void run_mergeSort_test(void)
{
    cunit_csv_load("test_cases_mergeSort.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *list_str = cunit_csv_cell_by_name(active_row, "list");
        int list[100];
        int list_count = 0;
        const char *p = list_str;
        while (*p && list_count < 100) {
            int val, n;
            if (sscanf(p, "%d%n", &val, &n) == 1) {
                list[list_count++] = val;
                p += n;
                if (*p == ',') p++;
            } else break;
        }
        int len; sscanf(cunit_csv_cell_by_name(active_row, "len"), "%d", &len);
        mergeSort(list, len);
        cunit_oracle_check_output("");
    }
    /* LLM_BODY_END */
}

void register_mergeSort(void)
{
    CU_add_test(cunit_suite, "mergeSort", run_mergeSort_test);
}
