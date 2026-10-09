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

static void run_pop_test(void)
{
    cunit_csv_load("test_cases_pop.csv");
    /* LLM_BODY_BEGIN */
    extern stack_link top;
    extern stack_link bottom;
    extern int size;
    int ret;
    char buf[64];
    const char *tn_str;
    int tn;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        tn_str = cunit_csv_cell_by_name(active_row, "test_number");
        tn = atoi(tn_str);
        top = NULL;
        bottom = NULL;
        size = 0;
        if (tn == 2) {
            push(10);
        } else if (tn == 3) {
            push(10);
            push(20);
        }
        cunit_capture_stdout_begin();
        ret = pop();
        cunit_capture_stdout_end();
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
        cunit_oracle_check_stdout();
    }
    /* LLM_BODY_END */
}

void register_pop(void)
{
    CU_add_test(cunit_suite, "pop", run_pop_test);
}
