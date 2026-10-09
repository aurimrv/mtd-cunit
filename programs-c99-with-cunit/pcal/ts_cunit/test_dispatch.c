#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Source-local typedefs and constants (verified at seed time). */
#define NUMWIDTH 71
#define NUMINDENT 4
#define DAYSTART 0
#define MONSTART 0
/* Project function prototypes (verified at seed time). */
extern void byebye(char *fmt, ...);
extern void getmmddyy(int *month, int *day, int *year);
extern int isleapyear(int year);
extern int jan1(int year);
extern int dayofweek(int month, int day, int year);
extern void genweek(int week[], int weeknum, int startday, int daysinweek, int numdays);
extern void genmonth(int month, int year);
extern void dispatch(int argc, char *argv[]);

static void run_dispatch_test(void)
{
    cunit_csv_load("test_cases_dispatch.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *test_str = cunit_csv_cell_by_name(active_row, "test_number");
        const char *argc_str = cunit_csv_cell_by_name(active_row, "argc");
        const char *argv_str = cunit_csv_cell_by_name(active_row, "argv");
        int test_num = atoi(test_str);
        int argc = atoi(argc_str);
        char buf[256];
        strncpy(buf, argv_str, sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';
        char *argv[20];
        int n = 0;
        char *tok = strtok(buf, " ");
        while (tok != NULL && n < 19) {
            argv[n++] = tok;
            tok = strtok(NULL, " ");
        }
        argv[n] = NULL;
        argc = n;

        cunit_capture_stdout_begin();
        if (test_num == 4 || test_num == 5) {
            cunit_expect_exit();
        }
        dispatch(argc, argv);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
    }
    /* LLM_BODY_END */
}

void register_dispatch(void)
{
    CU_add_test(cunit_suite, "dispatch", run_dispatch_test);
}
