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

static void run_schedule_test(void)
{
    cunit_csv_load("test_cases_schedule.csv");
    /* LLM_BODY_BEGIN */
        int i;
        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            const char *cmd_s = cunit_csv_cell_by_name(active_row, "command");
            const char *prio_s = cunit_csv_cell_by_name(active_row, "prio");
            const char *ratio_s = cunit_csv_cell_by_name(active_row, "ratio");
            int command = atoi(cmd_s);
            int prio = atoi(prio_s);
            float ratio = atof(ratio_s);
            char buf[64];
            cunit_capture_stdout_begin();
            int status = schedule(command, prio, ratio);
            cunit_capture_stdout_end();
            cunit_oracle_check_stdout();
            snprintf(buf, sizeof(buf), "%d", status);
            cunit_oracle_check_output(buf);
        }
    /* LLM_BODY_END */
}

void register_schedule(void)
{
    CU_add_test(cunit_suite, "schedule", run_schedule_test);
}
