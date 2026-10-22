#include "cunit_common.h"
#include "cunit_gcov.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule2.h"
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

static void cunit_sched_seed_jobs(int n_jobs, int prio)
{
    int i;
    int p = prio;
    if (p < 1) p = 1;
    if (p > 3) p = 3;
    for (i = 0; i < n_jobs; i++) new_job(p);
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
}

static void run_put_end_test(void)
{
    cunit_csv_load("test_cases_put_end.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        int prio = atoi(cunit_csv_cell_by_name(active_row, "prio"));
        int pid = atoi(cunit_csv_cell_by_name(active_row, "process"));
        int n_jobs = cunit_sched_n_jobs_cell();
        struct process *p = (struct process *)malloc(sizeof(struct process));
        int ret;
        cunit_sched_seed_jobs(n_jobs, prio);
        if (p == NULL) {
            cunit_oracle_check_output("malloc_fail");
            continue;
        }
        p->pid = (unsigned)pid;
        p->priority = prio;
        p->next = NULL;
        ret = put_end(prio, p);
        if (ret != 0) {
            free(p);
            cunit_sched_oracle_ret_flush(ret);
        } else {
            /* On success the queue owns p; flush() will free it. */
            cunit_sched_oracle_ret_flush(ret);
        }
    }
    /* LLM_BODY_END */
}

void register_put_end(void)
{
    CU_add_test(cunit_suite, "put_end", run_put_end_test);
}
