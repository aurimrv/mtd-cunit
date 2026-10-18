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

static void run_Own_Above_Threat_test(void)
{
    cunit_csv_load("test_cases_Own_Above_Threat.csv");
    /* LLM_BODY_BEGIN */
    extern int Other_Tracked_Alt;
    extern int Own_Tracked_Alt;
    char buf[32];
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        if (active_row == 0) {
            Other_Tracked_Alt = 0;
            Own_Tracked_Alt = 1;
        } else {
            Other_Tracked_Alt = 1;
            Own_Tracked_Alt = 0;
        }
        int result = Own_Above_Threat();
        snprintf(buf, sizeof(buf), "%d", result);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_Own_Above_Threat(void)
{
    CU_add_test(cunit_suite, "Own_Above_Threat", run_Own_Above_Threat_test);
}
