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

static void run_phi_test(void)
{
    cunit_csv_load("test_cases_phi.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        double x, mu, sigma;
        char buffer[64];
        sscanf(cunit_csv_cell_by_name(active_row, "x"), "%lf", &x);
        sscanf(cunit_csv_cell_by_name(active_row, "mu"), "%lf", &mu);
        sscanf(cunit_csv_cell_by_name(active_row, "sigma"), "%lf", &sigma);
        snprintf(buffer, sizeof(buffer), "%.17g", phi(x, mu, sigma));
        cunit_oracle_check_output(buffer);
    }
    /* LLM_BODY_END */
}

void register_phi(void)
{
    CU_add_test(cunit_suite, "phi", run_phi_test);
}
