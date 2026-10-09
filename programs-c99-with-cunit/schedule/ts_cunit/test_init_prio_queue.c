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

static void run_init_prio_queue_test(void)
{
    cunit_csv_load("test_cases_init_prio_queue.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *prio_str = cunit_csv_cell_by_name(active_row, "prio");
        const char *num_proc_str = cunit_csv_cell_by_name(active_row, "num_proc");
        int prio = atoi(prio_str);
        int num_proc = atoi(num_proc_str);
        init_prio_queue(prio, num_proc);
        cunit_oracle_check_output("");
    }
    /* LLM_BODY_END */
}

void register_init_prio_queue(void)
{
    CU_add_test(cunit_suite, "init_prio_queue", run_init_prio_queue_test);
}
