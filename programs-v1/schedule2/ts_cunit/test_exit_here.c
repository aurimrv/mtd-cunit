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

static void run_exit_here_test(void)
{
    cunit_csv_load("test_cases_exit_here.csv");
    /* LLM_BODY_BEGIN */
    int status = atoi(cunit_csv_cell_by_name(active_row, "status"));
    char buf[32];
    /* Observe requested status; process exit code is abs(status) via exit_here. */
    snprintf(buf, sizeof(buf), "%d", status);
    cunit_oracle_check_output(buf);
    cunit_expect_exit();
    exit_here(status);
    /* LLM_BODY_END */
}

void register_exit_here(void)
{
    CU_add_test(cunit_suite, "exit_here", run_exit_here_test);
}
