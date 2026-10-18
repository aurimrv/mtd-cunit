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

static void run_dispatch_test(void)
{
    cunit_csv_load("test_cases_dispatch.csv");
    /* LLM_BODY_BEGIN */
    extern FILE *mystdin;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *test_num_str = cunit_csv_cell_by_name(active_row, "test_number");
        int test_num = atoi(test_num_str);
        const char *input_str = "";
        switch (test_num) {
            case 1: input_str = ""; break;
            case 2: input_str = "6 3 5 7 99"; break;
            case 3: input_str = "4 1.5 2 2 0.5 1 2"; break;
            case 4: input_str = "2 4 0.5"; break;
            case 5: input_str = "1 0"; break;
            default: input_str = ""; break;
        }
        FILE *dummy = tmpfile();
        if (dummy) {
            mystdin = dummy;
            initialize();
            fclose(dummy);
        }
        FILE *fp = tmpfile();
        if (fp) {
            fprintf(fp, "%s", input_str);
            rewind(fp);
            mystdin = fp;
        }
        cunit_capture_stdout_begin();
        dispatch();
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
        cunit_oracle_check_output("");
        if (fp) {
            fclose(fp);
        }
    }
    /* LLM_BODY_END */
}

void register_dispatch(void)
{
    CU_add_test(cunit_suite, "dispatch", run_dispatch_test);
}
