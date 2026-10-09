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

static void run_Non_Crossing_Biased_Descend_test(void)
{
    cunit_csv_load("test_cases_Non_Crossing_Biased_Descend.csv");
    /* LLM_BODY_BEGIN */
    extern int Cur_Vertical_Sep;
    extern int Up_Separation;
    extern int Down_Separation;
    extern int Alt_Layer_Value;
    extern int Climb_Inhibit;
    extern int Own_Tracked_Alt;
    extern int Other_Tracked_Alt;
    extern int Positive_RA_Alt_Thresh[];
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *tn = cunit_csv_cell_by_name(active_row, "test_number");
        int test_num = atoi(tn);
        Climb_Inhibit = 0;
        Up_Separation = 0;
        Down_Separation = 0;
        Own_Tracked_Alt = 0;
        Other_Tracked_Alt = 0;
        Cur_Vertical_Sep = 0;
        Alt_Layer_Value = 0;
        Positive_RA_Alt_Thresh[0] = 0;
        if (test_num == 1) {
            Climb_Inhibit = 0;
            Up_Separation = 500;
            Down_Separation = 100;
            Own_Tracked_Alt = 1000;
            Other_Tracked_Alt = 900;
        } else if (test_num == 2) {
            Climb_Inhibit = 0;
            Up_Separation = 500;
            Down_Separation = 100;
            Own_Tracked_Alt = 900;
            Other_Tracked_Alt = 1000;
            Cur_Vertical_Sep = MINSEP + 100;
            Alt_Layer_Value = 0;
            Positive_RA_Alt_Thresh[0] = 50;
        } else if (test_num == 3) {
            Climb_Inhibit = 0;
            Up_Separation = 100;
            Down_Separation = 500;
            Own_Tracked_Alt = 900;
            Other_Tracked_Alt = 1000;
        } else if (test_num == 4) {
            Climb_Inhibit = 0;
            Up_Separation = 100;
            Down_Separation = 500;
            Own_Tracked_Alt = 1000;
            Other_Tracked_Alt = 900;
            Alt_Layer_Value = 0;
            Positive_RA_Alt_Thresh[0] = 200;
        } else if (test_num == 5) {
            Climb_Inhibit = 0;
            Up_Separation = 300;
            Down_Separation = 500;
            Own_Tracked_Alt = 1000;
            Other_Tracked_Alt = 900;
            Alt_Layer_Value = 0;
            Positive_RA_Alt_Thresh[0] = 200;
        }
        bool ret = Non_Crossing_Biased_Descend();
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", ret ? 1 : 0);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_Non_Crossing_Biased_Descend(void)
{
    CU_add_test(cunit_suite, "Non_Crossing_Biased_Descend", run_Non_Crossing_Biased_Descend_test);
}
