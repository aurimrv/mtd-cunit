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

/* Seed N jobs at a usable priority so queue side effects are observable via flush. */
static void cunit_sched_seed_jobs(int n_jobs, int prio)
{
    int i;
    int p = prio;
    if (p < 1) p = 1;
    if (p > 3) p = 3;
    for (i = 0; i < n_jobs; i++) {
        new_job(p);
    }
}

static int cunit_sched_n_jobs_cell(void)
{
    const char *nj = cunit_csv_cell_by_name(active_row, "n_jobs");
    if (nj == NULL || nj[0] == '\0') return 0;
    return atoi(nj);
}

static void cunit_sched_oracle_ret_flush(int ret)
{
    char buf[512];
    const char *cap;
    cunit_capture_stdout_begin();
    flush();
    cunit_capture_stdout_end();
    cap = cunit_capture_buf == NULL ? "" : cunit_capture_buf;
    snprintf(buf, sizeof(buf), "%d#%s", ret, cap);
    cunit_oracle_check_output(buf);
    if (cunit_has_column("expected_stdout")) {
        cunit_oracle_check_stdout();
    }
}

static void run_get_process_test(void)
{
    cunit_csv_load("test_cases_get_process.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *prio_str = cunit_csv_cell_by_name(active_row, "prio");
        const char *ratio_str = cunit_csv_cell_by_name(active_row, "ratio");
        int prio = atoi(prio_str);
        float ratio = (float)atof(ratio_str);
        int n_jobs = cunit_sched_n_jobs_cell();
        struct process *job = NULL;
        int ret;
        char buf[128];
        if (n_jobs <= 0) {
            /* legacy test_number-driven seed */
            const char *test_str = cunit_csv_cell_by_name(active_row, "test_number");
            int test = test_str ? atoi(test_str) : 0;
            if (test == 4) n_jobs = 1;
            else if (test == 5) n_jobs = 2;
        }
        cunit_sched_seed_jobs(n_jobs, prio);
        ret = get_process(prio, ratio, &job);
        snprintf(buf, sizeof(buf), "%d#%u", ret, job ? job->pid : 0u);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_get_process(void)
{
    CU_add_test(cunit_suite, "get_process", run_get_process_test);
}
