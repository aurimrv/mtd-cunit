#include	<ctype.h>
#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>

#include	"std.h"
#include	"chisq.h"
#include	"gamma.h"

#define	MAXLINE	256

#ifndef MAXTBL
#define	MAXTBL	1000
#endif

static char line[MAXLINE];
long f[MAXTBL];
int r;
int c;

#define	x(i,j)	f[(i)*c+(j)]

#define	COMMENT	'#'

FILE *mystdin;

int dispatch(void)
{
	char *p;
	int i;
	int j;
	double info;
	int infodf;
	double totinfo = 0.0;
	int totdf;

	totdf = 0;

	while (fgets(line, MAXLINE, mystdin) != NULL) {
		for (p = line; *p != '\0' && isspace((int)*p); ++p) ;

		if (*p == '\0')
			continue;

		if (*p == COMMENT) {
			(void)fputs(line, stdout);
			continue;
		}

		if (sscanf(p, "%d %d\n", &r, &c) != 2) {
			(void)fputs("* invalid row/column line *\n", stdout);
			return EXIT_FAILURE;
		}

		if (r * c > MAXTBL) {
			(void)fputs("* table too large *\n", stdout);
			return EXIT_FAILURE;
		}

		for (i = 0; i < r; ++i)
			for (j = 0; j < c; ++j)
				if (fscanf(mystdin, " %ld", &x(i, j)) != 1) {
					(void)fputs("* EOF in table *\n",
						    stdout);
					return EXIT_FAILURE;
				}

		info = InfoTbl(r, c, f, &infodf);

		if (info >= 0.0) {
			(void)printf("2info = %5.2f\tdf = %2d\tq = %7.4f\n",
				     info, infodf, QChiSq(info, infodf)
			    );
			totinfo += info;
			totdf += infodf;
		} else
			(void)fputs(info < -3.5 ? "out of memory\n"
				    : info < -2.5 ? "table too small\n"
				    : info < -1.5 ? "negative freq\n"
				    : "table all zeros\n", stdout);
	}

	if (totdf <= 0) {
		(void)fputs("\n*** no information accumulated ***\n", stdout);
		return EXIT_FAILURE;
	}

	(void)printf("\ntotal 2info = %5.2f\tdf = %2d\tq = %7.4f\n",
		     totinfo, totdf, QChiSq(totinfo, totdf)
	    );
	return EXIT_SUCCESS;
}

double LGamma(double x)
{
	static const double cof[6] = {
		76.18009173, -86.50532033, 24.01409822,
		-1.231739516, 0.120858003e-2, -0.536382e-5
	};
	double tmp, ser;
	int j;

	if (--x < 0.0) {
		double pix = PI * x;

		return log(pix / sin(pix)) - LGamma(1.0 - x);
	}

	tmp = x + 5.5;
	tmp -= (x + 0.5) * log(tmp);

	ser = 1.0;

	for (j = 0; j < 6; ++j)
		ser += cof[j] / ++x;

	return -tmp + log(2.50662827465 * ser);
}

#define	ITMAX	100
#define	EPS	3.0e-7

double gser(double a, double x)
{
	double ap, del, sum;
	int n;

	if (x <= 0.0)
		return 0.0;

	del = sum = 1.0 / (ap = a);

	for (n = 1; n <= ITMAX; ++n) {
		sum += del *= x / ++ap;

		if (Abs(del) < Abs(sum) * EPS)
			return sum * exp(-x + a * log(x) - LGamma(a));
	}

	return sum * exp(-x + a * log(x) - LGamma(a));
}

double gcf(double a, double x)
{
	int n;
	double gold = 0.0, fac = 1.0, b1 = 1.0, b0 = 0.0, a0 = 1.0, a1 = x;
	double g = 0.0;

	for (n = 1; n <= ITMAX; ++n) {
		double anf;
		double an = (double)n;
		double ana = an - a;

		a0 = (a1 + a0 * ana) * fac;
		b0 = (b1 + b0 * ana) * fac;
		anf = an * fac;
		b1 = x * b0 + anf * b1;
		a1 = x * a0 + anf * a1;

		if (a1 != 0.0) {
			g = b1 * (fac = 1.0 / a1);

			gold = g - gold;

			if (Abs(gold) < EPS * Abs(g))
				return exp(-x + a * log(x) - LGamma(a)) * g;

			gold = g;
		}
	}

	return exp(-x + a * log(x) - LGamma(a)) * g;
}

double QGamma(double a, double x)
{
	return x < a + 1.0 ? 1.0 - gser(a, x) : gcf(a, x);
}

double QChiSq(double chisq, int df)
{
	return QGamma((double)df / 2.0, chisq / 2.0);
}

double InfoTbl(int r, int c, const long *f, int *pdf)
{
	int i;
	int j;
	double N;
	double info = 0;
	double *xi;
	double *xj;
	int rdf = r - 1;
	int cdf = c - 1;

#undef x
#define	x(i,j)	f[(i)*c+(j)]

	if (rdf <= 0 || cdf <= 0) {
		info = -3.0;
		goto ret3;
	}

	*pdf = rdf * cdf;

	if ((xi = (double *)malloc(r * sizeof(double))) == NULL) {
		info = -4.0;
		goto ret3;
	}

	if ((xj = (double *)malloc(c * sizeof(double))) == NULL) {
		info = -4.0;
		goto ret2;
	}

	N = 0.0;

	for (i = 0; i < r; ++i) {
		double sum = 0.0;

		for (j = 0; j < c; ++j) {
			long k = x(i, j);

			if (k < 0L) {
				info = -2.0;
				goto ret1;
			}

			sum += (double)k;
		}

		N += xi[i] = sum;
	}

	if (N <= 0.0) {
		info = -1.0;
		goto ret1;
	}

	for (j = 0; j < c; ++j) {
		double sum = 0.0;

		for (i = 0; i < r; ++i)
			sum += (double)x(i, j);

		xj[j] = sum;
	}

	info = N * log(N);

	for (i = 0; i < r; ++i) {
		double pi = xi[i];

		if (pi > 0.0)
			info -= pi * log(pi);

		for (j = 0; j < c; ++j) {
			double pij = (double)x(i, j);

			if (pij > 0.0)
				info += pij * log(pij);
		}
	}

	for (j = 0; j < c; ++j) {
		double pj = xj[j];

		if (pj > 0.0)
			info -= pj * log(pj);
	}

	info *= 2.0;

 ret1:
	free((pointer) xj);
 ret2:
	free((pointer) xi);
 ret3:
	return info;
}
