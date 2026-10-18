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

static void run_Non_Crossing_Biased_Climb_test(void)
{
    cunit_csv_load("test_cases_Non_Crossing_Biased_Climb.csv");
    /* LLM_BODY_BEGIN */
    extern int Alt_Layer_Value;
    extern int Climb_Inhibit;
    extern int Cur_Vertical_Sep;
    extern int Down_Separation;
    extern int Other_Tracked_Alt;
    extern int Own_Tracked_Alt;
    extern int Positive_RA_Alt_Thresh[];
    extern int Up_Separation;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        Climb_Inhibit = 0;
        Up_Separation = 0;
        Down_Separation = 0;
        Own_Tracked_Alt = 0;
        Other_Tracked_Alt = 0;
        Alt_Layer_Value = 0;
        Positive_RA_Alt_Thresh[0] = 0;
        Cur_Vertical_Sep = 0;

        if (active_row == 0) {
            Down_Separation = -1;
            Own_Tracked_Alt = 1;
            Other_Tracked_Alt = 0;
        } else if (active_row == 1) {
            Down_Separation = -100;
            Own_Tracked_Alt = 0;
            Other_Tracked_Alt = 1;
            Positive_RA_Alt_Thresh[0] = -200;
        } else if (active_row == 2) {
            Down_Separation = -100;
            Own_Tracked_Alt = 0;
            Other_Tracked_Alt = 1;
            Positive_RA_Alt_Thresh[0] = 0;
        } else if (active_row == 3) {
            Down_Separation = 0;
            Own_Tracked_Alt = 0;
            Other_Tracked_Alt = 1;
        } else if (active_row == 4) {
            Down_Separation = 0;
            Own_Tracked_Alt = 1;
            Other_Tracked_Alt = 0;
            Cur_Vertical_Sep = MINSEP - 1;
        } else if (active_row == 5) {
            Down_Separation = 0;
            Up_Separation = 0;
            Own_Tracked_Alt = 1;
            Other_Tracked_Alt = 0;
            Cur_Vertical_Sep = MINSEP + 1;
            Positive_RA_Alt_Thresh[0] = 100;
        } else if (active_row == 6) {
            Down_Separation = 100;
            Up_Separation = 100;
            Own_Tracked_Alt = 1;
            Other_Tracked_Alt = 0;
            Cur_Vertical_Sep = MINSEP + 1;
            Positive_RA_Alt_Thresh[0] = 100;
        }

        int res = Non_Crossing_Biased_Climb();
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", res);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_Non_Crossing_Biased_Climb(void)
{
    CU_add_test(cunit_suite, "Non_Crossing_Biased_Climb", run_Non_Crossing_Biased_Climb_test);
}
