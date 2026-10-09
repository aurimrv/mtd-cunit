#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Project function prototypes (verified at seed time). */
extern int incrdate(int argc, char **argv);
extern void missing(void);
extern int printdate(int argc, char **argv);

static void run_incrdate_test(void)
{
    cunit_csv_load("test_cases_incrdate.csv");
    /* LLM_BODY_BEGIN */
    static char *unit[] = {"sec","min","hour","day","week","mon","year",""};
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *argc_str;
        const char *argv_str;
        int argc;
        char argv_buf[2048];
        char *argv[64];
        int i;
        char *tok;
        int will_exit;
        int sim_argc;
        char **sim_argv;
        int j;
        char c;
        int ret;
        char buf[32];

        argc_str = cunit_csv_cell_by_name(active_row, "argc");
        argv_str = cunit_csv_cell_by_name(active_row, "argv");
        argc = atoi(argc_str);
        strncpy(argv_buf, argv_str, sizeof(argv_buf) - 1);
        argv_buf[sizeof(argv_buf) - 1] = '\0';
        i = 0;
        tok = strtok(argv_buf, ",");
        while (tok && i < 64) {
            argv[i++] = tok;
            tok = strtok(NULL, ",");
        }

        will_exit = 0;
        if (argc >= 2) {
            sim_argc = argc - 2;
            sim_argv = argv + 2;
            while (sim_argc > 0) {
                c = **sim_argv;
                if (!(c == '.' || c == '-' || c == '+' || (c >= '0' && c <= '9'))) break;
                sim_argv++;
                sim_argc--;
                if (sim_argc == 0) { will_exit = 1; break; }
                for (j = 0; j < 7 && strncmp(sim_argv[0], unit[j], strlen(unit[j])) != 0; j++);
                if (j == 7) { will_exit = 1; break; }
                sim_argv++;
                sim_argc--;
            }
        }

        if (will_exit) {
            cunit_expect_exit();
            incrdate(argc, argv);
        } else {
            ret = incrdate(argc, argv);
            snprintf(buf, sizeof(buf), "%d", ret);
            cunit_oracle_check_output(buf);
        }
    }
    /* LLM_BODY_END */
}

void register_incrdate(void)
{
    CU_add_test(cunit_suite, "incrdate", run_incrdate_test);
}
