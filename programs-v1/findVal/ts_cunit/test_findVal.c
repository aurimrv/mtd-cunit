#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern int findVal(int numbers[], int length, int val);

static void run_findVal_test(void)
{
    cunit_csv_load("test_cases_findVal.csv");
    /* LLM_BODY_BEGIN */
    const char *numbers_cell;
    const char *length_cell;
    const char *val_cell;
    const char *p;
    int numbers[100];
    int length;
    int val;
    int i;
    int consumed;
    int result;
    char buffer[32];

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        numbers_cell = cunit_csv_cell_by_name(active_row, "numbers");
        length_cell = cunit_csv_cell_by_name(active_row, "length");
        val_cell = cunit_csv_cell_by_name(active_row, "val");
        sscanf(length_cell, "%d", &length);
        sscanf(val_cell, "%d", &val);
        p = numbers_cell;
        for (i = 0; i < length && i < 100; i++) {
            if (sscanf(p, "%d%n", &numbers[i], &consumed) != 1) {
                break;
            }
            p += consumed;
            if (*p == ',') {
                p++;
            }
        }
        if (length > 100) {
            length = 100;
        }
        result = findVal(numbers, length, val);
        snprintf(buffer, sizeof(buffer), "%d", result);
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_findVal(void)
{
    CU_add_test(cunit_suite, "findVal", run_findVal_test);
}
