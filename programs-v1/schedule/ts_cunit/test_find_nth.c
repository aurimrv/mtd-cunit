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

static void run_find_nth_test(void)
{
    cunit_csv_load("test_cases_find_nth.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *list_token = cunit_csv_cell_by_name(active_row, "f_list");
        const char *n_token = cunit_csv_cell_by_name(active_row, "n");
        List *f_list = NULL;
        int n = 0;
        Ele *result;
        char buffer[64];

        sscanf(n_token, "%d", &n);

        if (!list_token || list_token[0] == 'N') {
            f_list = NULL;
        } else if (list_token[0] == 'e') {
            f_list = new_list();
        } else if (list_token[0] == 'l') {
            f_list = new_list();
            f_list = append_ele(f_list, new_ele(10));
            f_list = append_ele(f_list, new_ele(20));
            if (list_token[4] == '3') {
                f_list = append_ele(f_list, new_ele(30));
            }
        }

        result = find_nth(f_list, n);
        if (result) {
            snprintf(buffer, sizeof(buffer), "%d", result->val);
        } else {
            snprintf(buffer, sizeof(buffer), "NULL");
        }
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_find_nth(void)
{
    CU_add_test(cunit_suite, "find_nth", run_find_nth_test);
}
