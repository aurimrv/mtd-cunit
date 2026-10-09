#include <stdio.h>
#include <string.h>

int less01(char *pq[], int i, int j)
{
	if (strcmp(pq[i - 1], pq[j - 1]) < 0)
		return 1;
	else
		return 0;
}

void exch(char *pq[], int i, int j)
{
	char *swap;
	swap = pq[i - 1];
	pq[i - 1] = pq[j - 1];
	pq[j - 1] = swap;
}

int less02(char *v, char *w)
{
	if (strcmp(v, w) < 0)
		return 1;
	else
		return 0;
}

void sink(char *pq[], int k, int N)
{
	int j;

	while (2 * k <= N) {
		j = 2 * k;
		if (j < N && less01(pq, j, j + 1))
			j++;
		if (!less01(pq, k, j))
			break;
		exch(pq, k, j);
		k = j;
	}
}

void sort(char *pq[], int length)
{
	int k;
	for (k = length / 2; k >= 1; k--)
		sink(pq, k, length);
	while (length > 1) {
		exch(pq, 1, length--);
		sink(pq, 1, length);
	}

}

int isSorted(char *a[], int length)
{
	int i;
	for (i = 1; i < length; i++)
		if (less02(a[i], a[i - 1]))
			return 0;
	return 1;
}

void show(char *a[], int length)
{
	int i;
	for (i = 0; i < length; i++) {
		printf("%s\n", a[i]);
	}
}
