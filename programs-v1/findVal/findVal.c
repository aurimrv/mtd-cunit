#include <stdio.h>

int findVal(int numbers[], int length, int val)
{
	int findVal = -1;
	int i;

	for (i = 0; i < length; i++)
		if (numbers[i] == val)
			findVal = i;

	return findVal;
}

int inArr[100];

