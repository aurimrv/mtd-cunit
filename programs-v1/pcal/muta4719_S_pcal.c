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
 printf("%-*.*s",4,4,spaces);
 printf
     ("|   SUN   |   MON   |   TUE   |   WED   |   THU   |   FRI   |   SAT   |\n");
 printf("%-*.*s",4,4,spaces);
 printf("%-*.*s\n", 71, 71, dashes);
 for (i = 0, j = 0; i < 7; i++)
  if (i >= startday)
   week[i] = ++j;
  else
   week[i] = 0;
 i = 7 - startday;
 genweek(week, weeknum, 1, i, numdays);
 for (k = 0; i < numdays; i += k, k = 0) {
  for (j = 0; j < 7; j++)
   if @
( ((i + month) < numdays) ) @

    week[j] = ++k + i;
   else
    week[j] = 0;
  if (k)
   genweek(week, ++weeknum, i + 1, k, numdays);
 }
}