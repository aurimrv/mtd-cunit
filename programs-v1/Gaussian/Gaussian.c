#include <stdio.h>
#include <math.h>

double Phi2(double, double, double);
double phi01(double);
double PhiInverse(double);
double Phi201(double);
double phi(double, double, double);
double PhiInverse02(double, double, double, double);

double phi01(double x)
{
	return exp(-x * x / 2) / sqrt(2 * M_PI);
}

double phi(double x, double mu, double sigma)
{
	return phi01((x - mu) / sigma) / sigma;
}

double Phi201(double z)
{
	double sum = 0.0, term = z;
	int i;

	if (z < -8.0)
		return 0.0;
	if (z > 8.0)
		return 1.0;

	for (i = 3; sum + term != sum; i += 2) {
		sum = sum + term;
		term = term * z * z / i;
	}
	return 0.5 + sum * phi01(z);
}

double Phi2(double z, double mu, double sigma)
{
	return Phi201((z - mu) / sigma);
}

double PhiInverse02(double y, double delta, double lo, double hi)
{
	double mid = lo + (hi - lo) / 2;
	if (hi - lo < delta)
		return mid;
	if (Phi201(mid) > y)
		return PhiInverse02(y, delta, lo, mid);
	else
		return PhiInverse02(y, delta, mid, hi);
}

double PhiInverse(double y)
{
	return PhiInverse02(y, .00000001, -8, 8);
}
