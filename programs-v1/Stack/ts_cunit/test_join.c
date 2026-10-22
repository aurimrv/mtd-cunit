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

static void run_join_test(void)
{
    cunit_csv_load("test_cases_join.csv");
    /* LLM_BODY_BEGIN */
    const char *above_tok;
    const char *below_tok;
    stack_list above_node;
    stack_list below_node;
    stack_link above;
    stack_link below;
    char buf[128];

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        above_tok = cunit_csv_cell_by_name(active_row, "above");
        below_tok = cunit_csv_cell_by_name(active_row, "below");
        above = NULL;
        below = NULL;
        if (above_tok && above_tok[0] == 'N' && above_tok[1] == 'O') {
            above_node.above = NULL;
            above_node.data = 11;
            above_node.below = NULL;
            above = &above_node;
        }
        if (below_tok && below_tok[0] == 'N' && below_tok[1] == 'O') {
            below_node.above = NULL;
            below_node.data = 22;
            below_node.below = NULL;
            below = &below_node;
        }
        join(above, below);
        snprintf(buf, sizeof(buf), "%d#%d#%d#%d",
                 above ? (above->below == below) : -1,
                 below ? (below->above == above) : -1,
                 above ? above->data : -1,
                 below ? below->data : -1);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_join(void)
{
    CU_add_test(cunit_suite, "join", run_join_test);
}
