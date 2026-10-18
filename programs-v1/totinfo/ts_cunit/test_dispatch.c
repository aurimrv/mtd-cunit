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

static void run_dispatch_test(void)
{
    cunit_csv_load("test_cases_dispatch.csv");
    /* LLM_BODY_BEGIN */
    extern FILE *mystdin;

    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *testnum = cunit_csv_cell_by_name(active_row, "test_number");
        int tn = atoi(testnum);
        const char *input = "";
        if (tn == 1) input = "";
        else if (tn == 2) input = "   \n# hello\n2 2\n1 1\n1 1\n";
        else if (tn == 3) input = "abc\n";
        else if (tn == 4) input = "1001 1\n";
        else if (tn == 5) input = "2 2\n1 2\n";
        else if (tn == 6) input = "2 2\n0 0\n0 0\n";
        else if (tn == 7) input = "2 2\n-1 1\n1 1\n";
        else if (tn == 8) input = "1 2\n1 1\n";

        FILE *tmp = tmpfile();
        if (tmp) {
            fputs(input, tmp);
            rewind(tmp);
            mystdin = tmp;
        }

        cunit_capture_stdout_begin();
        int ret = dispatch();
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();

        char buf[64];
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);

        if (tmp) fclose(tmp);
    }
    /* LLM_BODY_END */
}

void register_dispatch(void)
{
    CU_add_test(cunit_suite, "dispatch", run_dispatch_test);
}
