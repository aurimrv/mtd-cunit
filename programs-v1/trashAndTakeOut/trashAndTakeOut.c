#include <stdio.h>

void trash(int x)
{
	int m, n, o;

	m = 0;
	if (x > 0)
		m = 4;
	if (x > 5)
		n = 3 * m;
	else
		n = 4 * m;
	o = takeOut(m, n);
	printf("o is: %d\n", o);
}

int takeOut(int a, int b)
{
	int d, e;

	d = 42 * a;
	if (a > 0)
		e = 2 * b + d;
	else
		e = b + d;
	return e;
}

