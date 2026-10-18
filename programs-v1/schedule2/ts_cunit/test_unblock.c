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

static void run_unblock_test(void)
{
    cunit_csv_load("test_cases_unblock.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *ratio_str = cunit_csv_cell_by_name(active_row, "ratio");
        float ratio = 0.0f;
        sscanf(ratio_str, "%f", &ratio);

        if (ratio > 0.5f) {
            new_job(1);
            dispatch();
            block();
        }

        int ret = unblock(ratio);
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_unblock(void)
{
    CU_add_test(cunit_suite, "unblock", run_unblock_test);
}
