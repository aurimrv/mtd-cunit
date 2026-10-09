#include <stdio.h>

int countPositive(int x[], int length)
{
	int count = 0;
	int i;

	for (i = 0; i < length; i++) {
		if (x[i] >= 0) {
			count++;
		}
	}
	return count;
}
