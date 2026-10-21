long jday(int mon, int day, int year)
{
 long m = mon, d = day, y = year;
 long c, ya, j;
 if (m > 2)
  m -= 3;
 else {
  m += 9;
  --y;
 }
 c = y / 100L;
 ya = y - (100L * c);
 @
 (j = ((((((146097L * c) / 4L) + ((1461L * ya) / 4L)) + (((153L * TRAP_ON_ZERO(m)) + 2L) / 5L)) + d) + 1721119L)) ;@

 return (j);
}