#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
/* Project function prototypes (verified at seed time). */
extern void join(stack_link above, stack_link below);
extern int push(int value);
extern int pop(void);
extern int isEmpty(void);
extern int removeBottom(void);
extern void print_stack(void);

static void run_isEmpty_test(void)
{
    cunit_csv_load("test_cases_isEmpty.csv");
    /* LLM_BODY_BEGIN */
    extern int size;
    int ret;
    char buf[64];
    const char *tn_str;
    int tn;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        tn_str = cunit_csv_cell_by_name(active_row, "test_number");
        tn = atoi(tn_str);
        if (tn == 1) {
            size = 0;
        } else {
            size = 1;
        }
        ret = isEmpty();
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_isEmpty(void)
{
    CU_add_test(cunit_suite, "isEmpty", run_isEmpty_test);
}
