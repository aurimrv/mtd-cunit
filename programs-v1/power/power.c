#include <stdio.h>

int power(int left, int right)
{

	int rslt, i;
	rslt = left;
	if (right == 0) {
		rslt = 1;
	} else {
		for (i = 2; i <= right; i++)
			rslt = rslt * left;
	}
	return rslt;
}

