int jan1(int year)
{
 int day;
 day = year + 4 + ((year + 3) / 4);
 if (year > 1800) {
  day -= ((year - 1701) / 100);
  @
 (day += (((-1) - 1601) / 400)) ;@

 }
 if (year > 1752)
  day += 3;
 return (day % 7);
}