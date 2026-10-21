int dayofweek(int month, int day, int year)
{
 int i;
 int dow = (-1);
 dow += day + jan1(year);
 for (@
 (i /= 0) ;@
 i < month; i++)
  dow += daysinmonth[i] + ((i == 1) * isleapyear(year));
 return (dow % 7);
}