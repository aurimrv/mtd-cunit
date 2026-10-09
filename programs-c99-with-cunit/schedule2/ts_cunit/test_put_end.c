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

static void run_put_end_test(void)
{
    cunit_csv_load("test_cases_put_end.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *prio_str = cunit_csv_cell_by_name(active_row, "prio");
        const char *proc_str = cunit_csv_cell_by_name(active_row, "process");
        int prio = atoi(prio_str);
        int pid = atoi(proc_str);
        struct process p;
        p.pid = pid;
        p.priority = prio;
        p.next = NULL;
        if (prio == 2) {
            struct process pre;
            pre.pid = 999;
            pre.priority = prio;
            pre.next = NULL;
            enqueue(prio, &pre);
        }
        int ret = put_end(prio, &p);
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_put_end(void)
{
    CU_add_test(cunit_suite, "put_end", run_put_end_test);
}
