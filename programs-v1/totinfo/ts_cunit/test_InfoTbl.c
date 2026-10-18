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

static void run_InfoTbl_test(void)
{
    cunit_csv_load("test_cases_InfoTbl.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        int r = atoi(cunit_csv_cell_by_name(active_row, "r"));
        int c = atoi(cunit_csv_cell_by_name(active_row, "c"));
        const char *fstr = cunit_csv_cell_by_name(active_row, "f");
        long f_arr[1000];
        int n = 0;
        const char *p = fstr;
        while (*p && n < 1000) {
            char *end;
            long val = strtol(p, &end, 10);
            if (p == end) break;
            f_arr[n++] = val;
            p = end;
            if (*p == ',') p++;
        }
        int pdf = 0;
        double result = InfoTbl(r, c, f_arr, &pdf);
        char buf[64];
        snprintf(buf, sizeof(buf), "%.12g", result);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_InfoTbl(void)
{
    CU_add_test(cunit_suite, "InfoTbl", run_InfoTbl_test);
}
