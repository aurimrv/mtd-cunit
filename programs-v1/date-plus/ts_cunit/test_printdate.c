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

static void run_printdate_test(void)
{
    cunit_csv_load("test_cases_printdate.csv");
    /* LLM_BODY_BEGIN */
    extern long tloc;
    extern struct tm *ts;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *argc_str;
        const char *argv_str;
        int argc;
        char argv_buf[2048];
        char *argv[64];
        int i;
        char *tok;
        int will_exit;
        int k;
        char *fmt;
        char c;
        int ret;
        char buf[32];

        argc_str = cunit_csv_cell_by_name(active_row, "argc");
        argv_str = cunit_csv_cell_by_name(active_row, "argv");
        argc = atoi(argc_str);
        strncpy(argv_buf, argv_str, sizeof(argv_buf) - 1);
        argv_buf[sizeof(argv_buf) - 1] = '\0';
        i = 0;
        if (argc > 0) {
            tok = strtok(argv_buf, ",");
            while (tok && i < 64) {
                argv[i++] = tok;
                tok = strtok(NULL, ",");
            }
        }

        tloc = 0;
        ts = localtime(&tloc);

        will_exit = 0;
        if (argc > 0) {
            for (k = 0; k < argc && k < i; k++) {
                fmt = argv[k];
                while (*fmt) {
                    if (*fmt == '%') {
                        fmt++;
                        if (*fmt == '\0') break;
                        c = *fmt;
                        if (c != 'n' && c != 't' && c != 'S' && c != 'Z' && c != 'M' && c != 'H' && c != 'T' && c != 'd' && c != 'm' && c != 'h' && c != 'y' && c != 'w' && c != 'a' && c != 'D' && c != 'j') {
                            will_exit = 1;
                            break;
                        }
                    }
                    fmt++;
                }
                if (will_exit) break;
            }
        }

        if (will_exit) {
            cunit_capture_stdout_begin();
            cunit_expect_exit();
            printdate(argc, argv);
        } else {
            cunit_capture_stdout_begin();
            ret = printdate(argc, argv);
            cunit_capture_stdout_end();
            cunit_oracle_check_stdout();
            snprintf(buf, sizeof(buf), "%d", ret);
            cunit_oracle_check_output(buf);
        }
    }
    /* LLM_BODY_END */
}

void register_printdate(void)
{
    CU_add_test(cunit_suite, "printdate", run_printdate_test);
}
