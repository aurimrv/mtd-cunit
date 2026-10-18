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

static void run_schedule_test(void)
{
    cunit_csv_load("test_cases_schedule.csv");
    /* LLM_BODY_BEGIN */
    extern List *prio_queue[];
    extern Ele *cur_proc;
    int i;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        for (i = 1; i <= MAXPRIO; i++) {
            prio_queue[i] = new_list();
        }
        if (active_row == 1) {
            prio_queue[3] = append_ele(prio_queue[3], new_ele(1));
        } else if (active_row == 2) {
            prio_queue[2] = append_ele(prio_queue[2], new_ele(1));
        } else if (active_row == 3) {
            prio_queue[1] = append_ele(prio_queue[1], new_ele(1));
        }
        schedule();
    }
    /* LLM_BODY_END */
}

void register_schedule(void)
{
    CU_add_test(cunit_suite, "schedule", run_schedule_test);
}
