#include <stdio.h>
#include <string.h>

#define MAX 100
#define NOTFOUND -1

char subject[MAX];
char pattern[MAX];

int pat(char subject[], int subjectLen, char pattern[], int patternLen)
{

	int iSub = 0;
	int rtnIndex = NOTFOUND;
	int isPat = 0;
	int iPat = 0;

	while (isPat == 0 && (iSub + patternLen - 1 < subjectLen)) {
		if (subject[iSub] == pattern[0]) {
			rtnIndex = iSub;
			isPat = 1;
			for (iPat = 1; iPat < patternLen; iPat++) {
				if (subject[iSub + iPat] != pattern[iPat]) {
					rtnIndex = NOTFOUND;
					isPat = 0;
					break;
				}
			}
		}
		iSub++;
	}
	return rtnIndex;
}

