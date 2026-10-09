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

static void run_quantum_expire_test(void)
{
    cunit_csv_load("test_cases_quantum_expire.csv");
    /* LLM_BODY_BEGIN */
    extern Ele *cur_proc;
    extern List *prio_queue[];
    int i;
    const char *test_num_str;
    Ele *proc;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        test_num_str = cunit_csv_cell_by_name(active_row, "test_number");
        for (i = 0; i <= MAXPRIO; i++) {
            prio_queue[i] = new_list();
        }
        cur_proc = NULL;
        if (test_num_str[0] == '2') {
            proc = new_process(1);
            prio_queue[1] = append_ele(prio_queue[1], proc);
        }
        quantum_expire();
    }
    /* LLM_BODY_END */
}

void register_quantum_expire(void)
{
    CU_add_test(cunit_suite, "quantum_expire", run_quantum_expire_test);
}
