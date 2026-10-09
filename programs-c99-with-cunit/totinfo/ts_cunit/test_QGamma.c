#include "cunit_common.h"
#include "cunit_gcov.h"
#include	<ctype.h>
#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#define	x(i,j)	f[(i)*c+(j)]
#include "chisq.h"
#include "gamma.h"
#include "std.h"
/* Source-local typedefs and constants (verified at seed time). */
#define MAXLINE 256
#define COMMENT '#'
#define ITMAX 100
#define EPS 3.0e-7
/* Project function prototypes (verified at seed time). */
extern int dispatch(void);
extern double LGamma(double x);
extern double gser(double a, double x);
extern double gcf(double a, double x);
extern double QGamma(double a, double x);
extern double QChiSq(double chisq, int df);
extern double InfoTbl(int r, int c, const long *f, int *pdf);

static void run_QGamma_test(void)
{
    cunit_csv_load("test_cases_QGamma.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        double a = atof(cunit_csv_cell_by_name(active_row, "a"));
        double x = atof(cunit_csv_cell_by_name(active_row, "x"));
        double result = QGamma(a, x);
        char buf[64];
        snprintf(buf, sizeof(buf), "%.12g", result);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_QGamma(void)
{
    CU_add_test(cunit_suite, "QGamma", run_QGamma_test);
}
