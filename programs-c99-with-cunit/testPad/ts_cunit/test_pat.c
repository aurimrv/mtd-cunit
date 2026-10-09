#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <string.h>
/* Source-local typedefs and constants (verified at seed time). */
#define MAX 100
#define NOTFOUND -1
/* Project function prototypes (verified at seed time). */
extern int pat(char subject[], int subjectLen, char pattern[], int patternLen);

static void run_pat_test(void)
{
    cunit_csv_load("test_cases_pat.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *subjCell = cunit_csv_cell_by_name(active_row, "subject");
        const char *subjLenCell = cunit_csv_cell_by_name(active_row, "subjectLen");
        const char *patCell = cunit_csv_cell_by_name(active_row, "pattern");
        const char *patLenCell = cunit_csv_cell_by_name(active_row, "patternLen");
        int subjLen = 0;
        int patLen = 0;
        sscanf(subjLenCell, "%d", &subjLen);
        sscanf(patLenCell, "%d", &patLen);
        char subjBuf[256];
        char patBuf[256];
        strncpy(subjBuf, subjCell, sizeof(subjBuf) - 1);
        subjBuf[sizeof(subjBuf) - 1] = '\0';
        strncpy(patBuf, patCell, sizeof(patBuf) - 1);
        patBuf[sizeof(patBuf) - 1] = '\0';
        int result = pat(subjBuf, subjLen, patBuf, patLen);
        char outBuf[64];
        snprintf(outBuf, sizeof(outBuf), "%d", result);
        cunit_oracle_check_output(outBuf);
    }
    /* LLM_BODY_END */
}

void register_pat(void)
{
    CU_add_test(cunit_suite, "pat", run_pat_test);
}
