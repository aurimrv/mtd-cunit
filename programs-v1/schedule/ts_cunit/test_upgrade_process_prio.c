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

static void run_upgrade_process_prio_test(void)
{
    cunit_csv_load("test_cases_upgrade_process_prio.csv");
    /* LLM_BODY_BEGIN */
    extern List *prio_queue[];
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *test_str = cunit_csv_cell_by_name(active_row, "test_number");
        const char *prio_str = cunit_csv_cell_by_name(active_row, "prio");
        const char *ratio_str = cunit_csv_cell_by_name(active_row, "ratio");
        int test_num = atoi(test_str);
        int prio = atoi(prio_str);
        float ratio = (float)atof(ratio_str);
        if (test_num == 2) {
            List *src = new_list();
            List *dest = new_list();
            prio_queue[prio] = src;
            prio_queue[prio + 1] = dest;
        } else if (test_num == 3) {
            List *src = new_list();
            List *dest = new_list();
            Ele *e = new_ele(1);
            append_ele(src, e);
            prio_queue[prio] = src;
            prio_queue[prio + 1] = dest;
        } else if (test_num == 4) {
            List *src = new_list();
            List *dest = new_list();
            Ele *e = new_ele(1);
            append_ele(src, e);
            prio_queue[prio] = src;
            prio_queue[prio + 1] = dest;
        }
        upgrade_process_prio(prio, ratio);
        cunit_oracle_check_output("");
    }
    /* LLM_BODY_END */
}

void register_upgrade_process_prio(void)
{
    CU_add_test(cunit_suite, "upgrade_process_prio", run_upgrade_process_prio_test);
}
