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

static void run_append_ele_test(void)
{
    cunit_csv_load("test_cases_append_ele.csv");
    /* LLM_BODY_BEGIN */
    int val;
    const char *list_token;
    const char *ele_token;
    List *list;
    Ele *ele;
    Ele *pre;
    List *result;
    char buf[128];

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        list_token = cunit_csv_cell_by_name(active_row, "a_list");
        ele_token = cunit_csv_cell_by_name(active_row, "a_ele");
        sscanf(ele_token, "%d", &val);
        ele = new_ele(val);
        if (list_token[0] == 'N') {
            list = NULL;
        } else if (list_token[0] == 'e') {
            list = new_list();
        } else {
            list = new_list();
            pre = new_ele(0);
            list->first = pre;
            list->last = pre;
            list->mem_count = 1;
            pre->next = NULL;
            pre->prev = NULL;
        }
        result = append_ele(list, ele);
        snprintf(buf, sizeof(buf), "count=%d", result->mem_count);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_append_ele(void)
{
    CU_add_test(cunit_suite, "append_ele", run_append_ele_test);
}
