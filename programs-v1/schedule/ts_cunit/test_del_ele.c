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

static void run_del_ele_test(void)
{
    cunit_csv_load("test_cases_del_ele.csv");
    /* LLM_BODY_BEGIN */
    char buffer[64];
    const char *d_list_tok;
    const char *d_ele_tok;
    List *list;
    Ele *ele;
    List *ret;
    int n;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        d_list_tok = cunit_csv_cell_by_name(active_row, "d_list");
        d_ele_tok = cunit_csv_cell_by_name(active_row, "d_ele");
        list = NULL;
        ele = NULL;
        if (d_list_tok[0] != 'N') {
            if (d_list_tok[4] == '1') {
                list = new_list();
                list = append_ele(list, new_ele(1));
            } else if (d_list_tok[4] == '3') {
                list = new_list();
                list = append_ele(list, new_ele(1));
                list = append_ele(list, new_ele(2));
                list = append_ele(list, new_ele(3));
            }
        }
        if (d_ele_tok[0] != 'N') {
            n = d_ele_tok[0] - '0';
            if (list) {
                ele = find_nth(list, n);
            } else {
                ele = new_ele(n);
            }
        }
        ret = del_ele(list, ele);
        if (ret == NULL) {
            snprintf(buffer, sizeof(buffer), "NULL");
        } else {
            snprintf(buffer, sizeof(buffer), "non-NULL");
        }
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_del_ele(void)
{
    CU_add_test(cunit_suite, "del_ele", run_del_ele_test);
}
