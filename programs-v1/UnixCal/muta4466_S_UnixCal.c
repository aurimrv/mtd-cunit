int jan1(int yr)
{
 int y, d;
 y = yr;
 d = 4 + y + (y + 3) / 4;
 if (y > 1800) {
  @
 (d -= ((0 - 1701) / 100)) ;@

  d += (y - 1601) / 400;
 }
 if (y > 1752)
  d += 3;
 return (d % 7);
}