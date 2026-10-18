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

static void run_alt_sep_test_test(void)
{
    cunit_csv_load("test_cases_alt_sep_test.csv");
    /* LLM_BODY_BEGIN */
        extern int High_Confidence;
        extern int Own_Tracked_Alt_Rate;
        extern int Cur_Vertical_Sep;
        extern int Other_Capability;
        extern int Two_of_Three_Reports_Valid;
        extern int Other_RAC;
        extern int Climb_Inhibit;
        extern int Down_Separation;
        extern int Up_Separation;
        extern int Own_Tracked_Alt;
        extern int Other_Tracked_Alt;

        int ret;
        char buf[32];

        for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
            if (active_row == 0) {
                High_Confidence = 0;
                Own_Tracked_Alt_Rate = 0;
                Cur_Vertical_Sep = 0;
                Other_Capability = 0;
                Two_of_Three_Reports_Valid = 0;
                Other_RAC = 0;
                Climb_Inhibit = 0;
                Down_Separation = 0;
                Up_Separation = 0;
                Own_Tracked_Alt = 0;
                Other_Tracked_Alt = 0;
            } else if (active_row == 1) {
                High_Confidence = 1;
                Own_Tracked_Alt_Rate = 0;
                Cur_Vertical_Sep = 1000;
                Other_Capability = 1;
                Two_of_Three_Reports_Valid = 0;
                Other_RAC = 0;
                Climb_Inhibit = 0;
                Down_Separation = 0;
                Up_Separation = 0;
                Own_Tracked_Alt = 0;
                Other_Tracked_Alt = 0;
            } else if (active_row == 2) {
                High_Confidence = 1;
                Own_Tracked_Alt_Rate = 0;
                Cur_Vertical_Sep = 1000;
                Other_Capability = 0;
                Two_of_Three_Reports_Valid = 1;
                Other_RAC = 0;
                Climb_Inhibit = 700;
                Down_Separation = 300;
                Up_Separation = 300;
                Own_Tracked_Alt = 1000;
                Other_Tracked_Alt = 2000;
            } else if (active_row == 3) {
                High_Confidence = 1;
                Own_Tracked_Alt_Rate = 0;
                Cur_Vertical_Sep = 1000;
                Other_Capability = 0;
                Two_of_Three_Reports_Valid = 1;
                Other_RAC = 0;
                Climb_Inhibit = 100;
                Down_Separation = 0;
                Up_Separation = 300;
                Own_Tracked_Alt = 2000;
                Other_Tracked_Alt = 1000;
            } else if (active_row == 4) {
                High_Confidence = 1;
                Own_Tracked_Alt_Rate = 0;
                Cur_Vertical_Sep = 1000;
                Other_Capability = 0;
                Two_of_Three_Reports_Valid = 1;
                Other_RAC = 0;
                Climb_Inhibit = 0;
                Down_Separation = 0;
                Up_Separation = 0;
                Own_Tracked_Alt = 1000;
                Other_Tracked_Alt = 1000;
            }
            ret = alt_sep_test();
            snprintf(buf, sizeof(buf), "%d", ret);
            cunit_oracle_check_output(buf);
        }
    /* LLM_BODY_END */
}

void register_alt_sep_test(void)
{
    CU_add_test(cunit_suite, "alt_sep_test", run_alt_sep_test_test);
}
