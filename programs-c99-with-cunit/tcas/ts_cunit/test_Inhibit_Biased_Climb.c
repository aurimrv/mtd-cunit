#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
/* Source-local typedefs and constants (verified at seed time). */
#define OLEV 600
#define MAXALTDIFF 600
#define MINSEP 300
#define NOZCROSS 100
#define NO_INTENT 0
#define DO_NOT_CLIMB 1
#define DO_NOT_DESCEND 2
#define TCAS_TA 1
#define OTHER 2
#define UNRESOLVED 0
#define UPWARD_RA 1
#define DOWNWARD_RA 2
typedef int bool;
/* Project function prototypes (verified at seed time). */
extern void initialize(void);
extern int ALIM(void);
extern int Inhibit_Biased_Climb(void);
extern bool Non_Crossing_Biased_Climb(void);
extern bool Non_Crossing_Biased_Descend(void);
extern bool Own_Below_Threat(void);
extern bool Own_Above_Threat(void);
extern int alt_sep_test(void);

static void run_Inhibit_Biased_Climb_test(void)
{
    cunit_csv_load("test_cases_Inhibit_Biased_Climb.csv");
    /* LLM_BODY_BEGIN */
    extern int Climb_Inhibit;
    extern int Up_Separation;
    char buf[32];
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *tn = cunit_csv_cell_by_name(active_row, "test_number");
        if (tn[0] == '1') {
            Climb_Inhibit = 1;
            Up_Separation = 100;
        } else {
            Climb_Inhibit = 0;
            Up_Separation = 200;
        }
        int ret = Inhibit_Biased_Climb();
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_Inhibit_Biased_Climb(void)
{
    CU_add_test(cunit_suite, "Inhibit_Biased_Climb", run_Inhibit_Biased_Climb_test);
}
