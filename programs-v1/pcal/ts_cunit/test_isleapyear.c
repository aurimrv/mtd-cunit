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

static void run_isleapyear_test(void)
{
    cunit_csv_load("test_cases_isleapyear.csv");
    /* LLM_BODY_BEGIN */
        const char *cell;
        int year;
        int result;
        char buffer[32];

        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            cell = cunit_csv_cell_by_name(active_row, "year");
            year = atoi(cell);
            result = isleapyear(year);
            snprintf(buffer, sizeof(buffer), "%d", result);
            cunit_oracle_check_output(buffer);
        }
    /* LLM_BODY_END */
}

void register_isleapyear(void)
{
    CU_add_test(cunit_suite, "isleapyear", run_isleapyear_test);
}
