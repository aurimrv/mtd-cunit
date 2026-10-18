#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX	100

int minn(int a, int b)
{
	return a > b ? b : a;
}

void sort(char *a[], int sum)
{
	char *temp;
	int i, j;
	for (i = 0; i < sum - 1; i++)
		for (j = i + 1; j < sum; j++)
			if (strcmp(a[i], a[j]) > 0) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
}

char *substr(char *str, int star, int len)
{
	char *st;
	int l;
	l = len - star;
	st = malloc(sizeof(char) * (l + 1));
	strncpy(st, &str[star], l);
	st[l] = '\0';
	return st;
}

char *lcp(char s[], char t[])
{
	int i = 0, n;

	n = minn(strlen(s), strlen(t));
	for (i = 0; i < n; i++) {
		if (s[i] != t[i]) {
			return substr(s, 0, i);
		}
	}
	return substr(s, 0, n);
}

char *LRS(char s[])
{

	char *pp[MAX], *lrs = "", *p;
	int N = strlen(s);
	int i = 0;
	for (i = 0; i < N; i++) {
		p = substr(s, i, N);
		pp[i] = p;
	}

	sort(pp, N);

	for (i = 0; i < N - 1; i++) {
		char *str;

		str = lcp(pp[i], pp[i + 1]);

		if (strlen(str) > strlen(lrs)) {
			lrs = str;
		}

	}
	return lrs;
}

