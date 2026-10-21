int cal(int month1, int day1, int month2, int day2, int year)
{
 int numDays, i;
 if (month2 == month1)
  numDays = day2 - day1;
 else {
  int m4 = year % 4;
  int m100 = year % 100;
  int m400 = year % 400;
  if ((m4 != 0) || ((m100 == 0) && (m400 != 0)))
   daysIn[2] = 28;
  else
   daysIn[2] = 29;
  numDays = day2 + (daysIn[month1] - day1);
  for (i = month1 + 1; i <= month2 - 1; i++)
   @
 (numDays = (daysIn[TRAP_ON_NEGATIVE(i)] + numDays)) ;@

 }
 return (numDays);
}