#include "cunit_common.h"
#include "cunit_gcov.h"
#include <math.h>
#include <stdio.h>
/* Project function prototypes (verified at seed time). */
extern double phi01(double x);
extern double phi(double x, double mu, double sigma);
extern double Phi201(double z);
extern double Phi2(double z, double mu, double sigma);
extern double PhiInverse02(double y, double delta, double lo, double hi);
extern double PhiInverse(double y);

static void run_PhiInverse02_test(void)
{
    cunit_csv_load("test_cases_PhiInverse02.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        double y, delta, lo, hi;
        char buffer[64];
        sscanf(cunit_csv_cell_by_name(active_row, "y"), "%lf", &y);
        sscanf(cunit_csv_cell_by_name(active_row, "delta"), "%lf", &delta);
        sscanf(cunit_csv_cell_by_name(active_row, "lo"), "%lf", &lo);
        sscanf(cunit_csv_cell_by_name(active_row, "hi"), "%lf", &hi);
        snprintf(buffer, sizeof(buffer), "%.17g", PhiInverse02(y, delta, lo, hi));
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_PhiInverse02(void)
{
    CU_add_test(cunit_suite, "PhiInverse02", run_PhiInverse02_test);
}
