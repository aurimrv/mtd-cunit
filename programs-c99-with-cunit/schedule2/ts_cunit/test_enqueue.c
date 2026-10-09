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

static void run_enqueue_test(void)
{
    cunit_csv_load("test_cases_enqueue.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *ps = cunit_csv_cell_by_name(active_row, "prio");
        int prio = 0;
        int sign = 1;
        if (ps) {
            if (*ps == '-') { sign = -1; ps++; }
            while (*ps >= '0' && *ps <= '9') {
                prio = prio * 10 + (*ps - '0');
                ps++;
            }
            prio *= sign;
        }
        const char *np = cunit_csv_cell_by_name(active_row, "new_process");
        struct process proc;
        proc.pid = 1;
        if (np && np[0] >= '0' && np[0] <= '9') proc.pid = (unsigned int)(np[0] - '0');
        proc.priority = prio;
        proc.next = NULL;
        int ret = enqueue(prio, &proc);
        char buf[64];
        snprintf(buf, sizeof buf, "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_enqueue(void)
{
    CU_add_test(cunit_suite, "enqueue", run_enqueue_test);
}
