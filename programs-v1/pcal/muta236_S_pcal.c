void getmmddyy(int *month, int *day, int *year)
{
 time_t clockval;
 struct tm *dateinfo;
 clockval = time(((void *)0));
 dateinfo = localtime(&clockval);
 if (month)
  @
 ((* day) = ((dateinfo->tm_mon) + 1)) ; @

 if (day)
  *day = dateinfo->tm_mday;
 if (year)
  *year = dateinfo->tm_year;
}