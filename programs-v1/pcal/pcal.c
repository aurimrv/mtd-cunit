#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUMWIDTH 71

#define NUMINDENT 4

#define INDENT() printf("%-*.*s",NUMINDENT,NUMINDENT,spaces)

#define THESPLIT (weeknum == 5) && (endday < numdays) && (week[i]+7 <= numdays)

static char *spaces = "                                                   ";
static char *dashes =
    "-------------------------------------------------------------------------------";

static int daysinmonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char *monthnames[] = { "January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November",
	"December"
};

char *daynames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

#define DAYSTART 0

#define MONSTART 0

void byebye(char *fmt, ...)
{
	if (fmt != NULL) {
		va_list ap;
		va_start(ap, fmt);
		vprintf(fmt, ap);
		va_end(ap);
	}

	printf("\n");
	printf("Usage: pcal [-l] [-m startmonth]\n");
	printf("            [-n nummonths] [-u] [-y startyear]\n");
	printf("       startmonth:day of month to start on(1=jan...12=dec)\n");
	printf("       startyear :year to start on(1989=1989, 89=0089)\n");
	printf("                  default startday=1, startmonth=1,\n");
	printf("                  startyear=current year\n");
	printf("       nummonths :#of months to print out(default is 12)\n");
	printf
	    ("       -l        :suppress printing of ^L's after each month\n");
	printf("                  default is to print them\n");
	printf("       -u        :print this synopsis\n");

	exit(0);
}

void getmmddyy(int *month, int *day, int *year)
{
	time_t clockval;
	struct tm *dateinfo;

	clockval = time(NULL);

	dateinfo = localtime(&clockval);
	if (month)
		*month = dateinfo->tm_mon + 1;
	if (day)
		*day = dateinfo->tm_mday;
	if (year)
		*year = dateinfo->tm_year;
}

int isleapyear(int year)
{
	return ((!(year % 4)) && (year % 100) ? 1 : 0);
}

int jan1(int year)
{
	int day;

	day = year + 4 + ((year + 3) / 4);
	if (year > 1800) {
		day -= ((year - 1701) / 100);
		day += ((year - 1601) / 400);
	}
	if (year > 1752)
		day += 3;
	return (day % 7);
}

int dayofweek(int month, int day, int year)
{
	int i;
	int dow = (-1);

	dow += day + jan1(year);

	for (i = 0; i < month; i++)
		dow += daysinmonth[i] + ((i == 1) * isleapyear(year));

	return (dow % 7);
}

void genweek(int week[], int weeknum, int startday, int daysinweek, int numdays)
{
	int i;
	int row;
	int endday;

	if (weeknum > 5)
		return;

	endday = startday + daysinweek - 1;

	for (row = 0; row < 5; row++) {
		INDENT();
		printf("|");

		for (i = 0; i < 7; i++) {

			if (week[i]) {
				switch (row) {
				case 0:
					printf("%2d|    %s", week[i],
					       (THESPLIT) ? "_/" : "  ");
					break;

				case 1:
					printf("---  %s  ",
					       (THESPLIT) ? "_/" : "  ");
					break;

				case 2:
					printf("   %s    ",
					       (THESPLIT) ? "_/" : "  ");
					break;

				case 3:
					printf(" %s",
					       (THESPLIT) ? "_/   ---" :
					       "        ");
					break;

				case 4:
					if (THESPLIT)
						printf("/     |%2d",
						       week[i] + 7);
					else
						printf("         ");
					break;
				}
			} else
				printf("%-9.9s", spaces);
			printf("|");
		}

		printf("\n");
	}

	INDENT();
	printf("%-*.*s\n", NUMWIDTH, NUMWIDTH, dashes);
}

void genmonth(int month, int year)
{
	int i, j, k;
	int startday;
	int numdays;
	int weeknum = 1;
	int week[7];

	i = (80 - (int)strlen(monthnames[month])) / 2;

	printf("%-*.*s%-s\n\n", i, i, spaces, monthnames[month]);

	numdays = daysinmonth[month] + ((month == 1) * isleapyear(year));

	startday = dayofweek(month, 1, year);

	INDENT();
	printf
	    ("|   SUN   |   MON   |   TUE   |   WED   |   THU   |   FRI   |   SAT   |\n");
	INDENT();
	printf("%-*.*s\n", NUMWIDTH, NUMWIDTH, dashes);

	for (i = 0, j = 0; i < 7; i++)
		if (i >= startday)
			week[i] = ++j;
		else
			week[i] = 0;

	i = 7 - startday;
	genweek(week, weeknum, 1, i, numdays);

	for (k = 0; i < numdays; i += k, k = 0) {
		for (j = 0; j < 7; j++)
			if ((i + k) < numdays)
				week[j] = ++k + i;
			else
				week[j] = 0;
		if (k)
			genweek(week, ++weeknum, i + 1, k, numdays);
	}
}

void dispatch(int argc, char *argv[])
{
	int i;
	int curmonth = 1;
	int curyear;
	int nummonths = 12;
	int controll = 0;

	getmmddyy(0, 0, &curyear);
	curyear += 1900;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'm':
				if (++i == argc)
					byebye("-m requires integer arguement");
				else if ((sscanf(argv[i], "%d", &curmonth) != 1)
					 || (curmonth < 1) || (curmonth > 12))
					byebye("Bad arg '%s' for -m flag\n",
					       argv[i]);
				break;

			case 'n':
				if (++i == argc)
					byebye("-n requires integer arguement");
				else if ((sscanf(argv[i], "%d", &nummonths) !=
					  1) || (nummonths < 1))
					byebye("Bad arg '%s' for -n flag\n",
					       argv[i]);
				break;

			case 'y':
				if (++i == argc)
					byebye("-y requires integer arguement");
				else if (sscanf(argv[i], "%d", &curyear) != 1)
					byebye("Bad arg '%s' for -y flag\n",
					       argv[i]);
				break;

			case 'l':
				controll = 1;
				break;

			case 'u':
				byebye(NULL);
				break;

			default:
				byebye("Bad command line arguement: %s",
				       argv[i]);
				break;
			}
		} else
			byebye("Bad command line arguement: %s", argv[i]);
	}

	curmonth--;

	for (; nummonths > 0; nummonths--, curmonth++) {
		if (curmonth == 12) {
			curmonth = 0;
			curyear++;
		}

		printf("\n\n\n%-*.*s%-4d\n\n", 38, 38, spaces, curyear);

		genmonth(curmonth, curyear);

		if (!controll)
			printf("       \014\n");
	}

}
