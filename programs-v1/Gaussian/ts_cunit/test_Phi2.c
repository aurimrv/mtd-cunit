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

static void run_Phi2_test(void)
{
    cunit_csv_load("test_cases_Phi2.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        double z, mu, sigma;
        char buffer[64];
        sscanf(cunit_csv_cell_by_name(active_row, "z"), "%lf", &z);
        sscanf(cunit_csv_cell_by_name(active_row, "mu"), "%lf", &mu);
        sscanf(cunit_csv_cell_by_name(active_row, "sigma"), "%lf", &sigma);
        snprintf(buffer, sizeof(buffer), "%.17g", Phi2(z, mu, sigma));
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_Phi2(void)
{
    CU_add_test(cunit_suite, "Phi2", run_Phi2_test);
}
