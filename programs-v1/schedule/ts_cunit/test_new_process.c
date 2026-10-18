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

static void run_new_process_test(void)
{
    cunit_csv_load("test_cases_new_process.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *prio_str = cunit_csv_cell_by_name(active_row, "prio");
        int prio = atoi(prio_str);
        Ele *proc = new_process(prio);
        char buf[64];
        snprintf(buf, sizeof(buf), "%p", (void*)proc);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_new_process(void)
{
    CU_add_test(cunit_suite, "new_process", run_new_process_test);
}
