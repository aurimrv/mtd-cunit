int jan1(int year)
{
 int day;
 day = year + 4 + ((year + 3) / 4);
 @
return (day % 7);@
if (year > 1752)
  day += 3;
 return (day % 7);
}