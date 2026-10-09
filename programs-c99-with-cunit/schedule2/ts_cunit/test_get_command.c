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

static void run_get_command_test(void)
{
    cunit_csv_load("test_cases_get_command.csv");
    /* LLM_BODY_BEGIN */
    extern FILE *mystdin;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        int command = 0;
        int prio = 0;
        float ratio = 0.0f;
        sscanf(cunit_csv_cell_by_name(active_row, "command"), "%d", &command);
        sscanf(cunit_csv_cell_by_name(active_row, "prio"), "%d", &prio);
        sscanf(cunit_csv_cell_by_name(active_row, "ratio"), "%f", &ratio);
        char input[256];
        input[0] = '\0';
        switch (command) {
            case 0: break;
            case 1: snprintf(input, sizeof(input), "1 2\n"); break;
            case 4: snprintf(input, sizeof(input), "4 0.5\n"); break;
            case 2: snprintf(input, sizeof(input), "2 3 0.7\n"); break;
            case 7: snprintf(input, sizeof(input), "7"); break;
            default: break;
        }
        FILE *fp = tmpfile();
        if (fp != NULL) {
            if (input[0] != '\0') {
                fputs(input, fp);
            }
            rewind(fp);
            mystdin = fp;
            int ret = get_command(&command, &prio, &ratio);
            char out[32];
            snprintf(out, sizeof(out), "%d", ret);
            cunit_oracle_check_output(out);
            fclose(fp);
        }
    }
    /* LLM_BODY_END */
}

void register_get_command(void)
{
    CU_add_test(cunit_suite, "get_command", run_get_command_test);
}
