#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
/* Project function prototypes (verified at seed time). */
extern void dispatch(int argc, char *argv[]);
extern void pstr(char *str, int n);
extern void cal(int m, int y, char *p, int w);
extern int jan1(int yr);

static void run_dispatch_test(void)
{
    cunit_csv_load("test_cases_dispatch.csv");
    /* LLM_BODY_BEGIN */
        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            const char *argc_cell = cunit_csv_cell_by_name(active_row, "argc");
            const char *argv_cell = cunit_csv_cell_by_name(active_row, "argv");
            int argc = atoi(argc_cell);
            char argv_buf[256];
            int i;
            for (i = 0; argv_cell[i] != '\0' && i < 255; i++) {
                argv_buf[i] = argv_cell[i];
            }
            argv_buf[i] = '\0';
            char *argv[10];
            int argc_built = 0;
            char *p = argv_buf;
            while (*p && argc_built < argc && argc_built < 9) {
                argv[argc_built++] = p;
                while (*p && *p != ',') p++;
                if (*p == ',') {
                    *p = '\0';
                    p++;
                }
            }
            argv[argc_built] = NULL;
            cunit_expect_exit();
            cunit_capture_stdout_begin();
            dispatch(argc, argv);
        }
    /* LLM_BODY_END */
}

void register_dispatch(void)
{
    CU_add_test(cunit_suite, "dispatch", run_dispatch_test);
}
