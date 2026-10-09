#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern void arraycopy(int *src, int srcstart, int *dest, int deststart, int length);
extern void mergeSort(int *list, int len);
extern void merge(int *list1, int list1len, int *list2, int list2len, int *temp);

static void run_merge_test(void)
{
    cunit_csv_load("test_cases_merge.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *list1_str = cunit_csv_cell_by_name(active_row, "list1");
        int list1[100];
        int list1_count = 0;
        const char *p = list1_str;
        while (*p && list1_count < 100) {
            int val, n;
            if (sscanf(p, "%d%n", &val, &n) == 1) {
                list1[list1_count++] = val;
                p += n;
                if (*p == ',') p++;
            } else break;
        }
        const char *list2_str = cunit_csv_cell_by_name(active_row, "list2");
        int list2[100];
        int list2_count = 0;
        p = list2_str;
        while (*p && list2_count < 100) {
            int val, n;
            if (sscanf(p, "%d%n", &val, &n) == 1) {
                list2[list2_count++] = val;
                p += n;
                if (*p == ',') p++;
            } else break;
        }
        const char *temp_str = cunit_csv_cell_by_name(active_row, "temp");
        int temp[200];
        int temp_count = 0;
        p = temp_str;
        while (*p && temp_count < 200) {
            int val, n;
            if (sscanf(p, "%d%n", &val, &n) == 1) {
                temp[temp_count++] = val;
                p += n;
                if (*p == ',') p++;
            } else break;
        }
        int list1len; sscanf(cunit_csv_cell_by_name(active_row, "list1len"), "%d", &list1len);
        int list2len; sscanf(cunit_csv_cell_by_name(active_row, "list2len"), "%d", &list2len);
        merge(list1, list1len, list2, list2len, temp);
        cunit_oracle_check_output("");
    }
    /* LLM_BODY_END */
}

void register_merge(void)
{
    CU_add_test(cunit_suite, "merge", run_merge_test);
}
