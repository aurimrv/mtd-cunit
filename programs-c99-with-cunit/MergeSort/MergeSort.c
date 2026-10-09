#include <stdio.h>

void merge(int *list1, int list1len, int *list2, int list2len, int *temp);

void arraycopy(int *src, int srcstart, int *dest, int deststart, int length)
{
	int i = 0;
	while (i < length) {
		dest[deststart + i] = src[srcstart + i];
		i++;
	}

}

void mergeSort(int *list, int len)
{
	int firstHalf[len / 2];
	int secondHalfLength = len - len / 2;
	int secondHalf[secondHalfLength];
	if (len > 1) {

		arraycopy(list, 0, firstHalf, 0, len / 2);

		mergeSort(firstHalf, len / 2);

		arraycopy(list, len / 2, secondHalf, 0, secondHalfLength);

		mergeSort(secondHalf, secondHalfLength);

		merge(firstHalf, len / 2, secondHalf, secondHalfLength, list);
	}
}

void merge(int *list1, int list1len, int *list2, int list2len, int *temp)
{
	int current1 = 0;
	int current2 = 0;
	int current3 = 0;

	while (current1 < list1len && current2 < list2len) {
		if (list1[current1] < list2[current2])
			temp[current3++] = list1[current1++];
		else
			temp[current3++] = list2[current2++];
	}

	while (current1 < list1len)
		temp[current3++] = list1[current1++];

	while (current2 < list2len)
		temp[current3++] = list2[current2++];
}


