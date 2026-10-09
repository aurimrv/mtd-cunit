#include <stdio.h>

int FnNegate(int a)
{
	int neg = 0;
	int d = a < 0 ? 1 : -1;
	while (a != 0) {
		neg += d;
		a += d;
	}
	return neg;
}

int FnMinus(int a, int b)
{
	return a + FnNegate(b);
}

int DifferentSigns(int a, int b)
{
	return ((a < 0 && b > 0) || (a > 0 && b < 0)) ? 1 : 0;
}

int abss(int a)
{
	if (a < 0)
		return FnNegate(a);
	else
		return a;
}

int FnTimes(int a, int b)
{
	int sum = 0;
	int iter;
	if (a < b)
		return FnTimes(b, a);	
	for (iter = abss(b); iter > 0; --iter) {
		sum += a;
	}
	if (b < 0)
		sum = FnNegate(sum);
	return sum;
}

int DefineAndRoundFraction(int a, int b)
{
	if (FnTimes(abss(a), 2) >= abss(b))
		return 1;
	else
		return 0;
}

int FnDivide(int a, int b)
{
	int quotient = 0;
	int divisor = 0;
	int divend;
	if (b == 0) {
		printf("ERROR: Divide by zero.");
		return 0;
	}
	divisor = FnNegate(abss(b));
	divend = abss(a);
	for (divend = abss(a); divend >= abss(divisor); divend += divisor) {
		++quotient;
	}

	if (DifferentSigns(a, b) == 1)
		quotient = FnNegate(quotient);
	return quotient;
}
