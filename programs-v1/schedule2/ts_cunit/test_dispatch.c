#include "cunit_common.h"
#include "cunit_gcov.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule2.h"
/* Project function prototypes (verified at seed time). */
extern int enqueue(int prio, struct process *new_process);
extern void dispatch(void);
extern int get_command(int *command, int *prio, float *ratio);
extern void exit_here(int status);
extern int new_job(int prio);
extern int upgrade_prio(int prio, float ratio);
extern int block(void);
extern int unblock(float ratio);
extern int quantum_expire(void);
extern int finish(void);
extern int flush(void);
extern struct process *get_current(void);
extern int reschedule(int prio);
extern int schedule(int command, int prio, float ratio);
extern int put_end(int prio, struct process *process);
extern int get_process(int prio, float ratio, struct process **job);

static void run_dispatch_test(void)
{
    cunit_csv_load("test_cases_dispatch.csv");
    /* LLM_BODY_BEGIN */
    extern FILE *mystdin;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *tn = cunit_csv_cell_by_name(active_row, "test_number");
        int test_num = atoi(tn);
        FILE *fp = tmpfile();
        if (test_num == 1) {
            /* empty */
        } else if (test_num == 2) {
            fprintf(fp, "1 2 0.5\n");
        } else if (test_num == 3) {
            fprintf(fp, "1\n");
        }
        rewind(fp);
        mystdin = fp;
        cunit_expect_exit();
        dispatch();
    }
    /* LLM_BODY_END */
}

void register_dispatch(void)
{
    CU_add_test(cunit_suite, "dispatch", run_dispatch_test);
}
