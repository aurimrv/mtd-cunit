#include "cunit_common.h"
#include "cunit_gcov.h"
#include <malloc.h>
#include <stdio.h>
#include "schedule.h"
/* Project function prototypes (verified at seed time). */
extern Ele * new_ele(int new_num);
extern List *new_list(void);
extern List *append_ele(List *a_list, Ele *a_ele);
extern Ele *find_nth(List *f_list, int n);
extern List *del_ele(List *d_list, Ele *d_ele);
extern void free_ele(Ele *ptr);
extern void finish_process(void);
extern void finish_all_processes(void);
extern void schedule(void);
extern void upgrade_process_prio(int prio, float ratio);
extern void unblock_process(float ratio);
extern void quantum_expire(void);
extern void block_process(void);
extern Ele * new_process(int prio);
extern void add_process(int prio);
extern void init_prio_queue(int prio, int num_proc);
extern void initialize(void);
extern void dispatch(void);

static void run_unblock_process_test(void)
{
    cunit_csv_load("test_cases_unblock_process.csv");
    /* LLM_BODY_BEGIN */
    extern List *block_queue;
    extern List *prio_queue[];

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *ratio_str = cunit_csv_cell_by_name(active_row, "ratio");
        float ratio = (float)atof(ratio_str);

        block_queue = NULL;

        if (active_row == 0) {
            block_queue = NULL;
        } else if (active_row == 1) {
            block_queue = new_list();
        } else {
            Ele *e = new_ele(1);
            e->priority = 0;
            block_queue = new_list();
            append_ele(block_queue, e);
            prio_queue[0] = new_list();
        }

        unblock_process(ratio);
    }
    /* LLM_BODY_END */
}

void register_unblock_process(void)
{
    CU_add_test(cunit_suite, "unblock_process", run_unblock_process_test);
}
