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

static void run_push_test(void)
{
    cunit_csv_load("test_cases_push.csv");
    /* LLM_BODY_BEGIN */
    extern stack_link top;
    extern stack_link bottom;
    extern int size;
    int value;
    int ret;
    char buf[128];
    const char *tn_str;
    int tn;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        tn_str = cunit_csv_cell_by_name(active_row, "test_number");
        tn = atoi(tn_str);
        value = atoi(cunit_csv_cell_by_name(active_row, "value"));
        top = NULL;
        bottom = NULL;
        size = 0;
        if (tn == 2) {
            size = 1;
        }
        ret = push(value);
        snprintf(buf, sizeof(buf), "%d#%d#%d", ret, size, top ? top->data : -999);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_push(void)
{
    CU_add_test(cunit_suite, "push", run_push_test);
}
