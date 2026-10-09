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

static void run_get_current_test(void)
{
    cunit_csv_load("test_cases_get_current.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *test_num_str = cunit_csv_cell_by_name(active_row, "test_number");
        int test_num = atoi(test_num_str);
        struct process *job = NULL;
        struct process p;
        char buf[64];
        if (test_num == 1) {
            new_job(1);
            job = get_current();
        } else if (test_num == 2) {
            p.pid = 42;
            p.priority = 2;
            p.next = NULL;
            put_end(2, &p);
            job = get_current();
        } else if (test_num == 3) {
            p.pid = 99;
            p.priority = 0;
            p.next = NULL;
            put_end(0, &p);
            job = get_current();
        }
        if (job) {
            snprintf(buf, sizeof(buf), "%u", job->pid);
        } else {
            snprintf(buf, sizeof(buf), "NULL");
        }
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_get_current(void)
{
    CU_add_test(cunit_suite, "get_current", run_get_current_test);
}
