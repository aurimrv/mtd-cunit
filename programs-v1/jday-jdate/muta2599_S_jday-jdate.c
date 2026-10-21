int *jdate(long j)
{
 static int ret[4];
 long d, m, y;
 ret[3] = (j + 1L) % 7L;
 j -= 1721119L;
 @
 (y = (((4L * TRAP_ON_NEGATIVE(j)) - 1L) / 146097L)) ;@

 j = 4L * j - 1L - 146097L * y;
 d = j / 4L;
 j = (4L * d + 3L) / 1461L;
 d = 4L * d + 3L - 1461L * j;
 d = (d + 4L) / 4L;
 m = (5L * d - 3L) / 153L;
 d = 5L * d - 3 - 153L * m;
 d = (d + 5L) / 5L;
 y = 100L * y + j;
 if (m < 10)
  m += 3;
 else {
  m -= 9;
  ++y;
 }
 ret[0] = m;
 ret[1] = d;
 ret[2] = y;
 return (ret);
}