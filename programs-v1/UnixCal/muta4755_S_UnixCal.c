int jan1(int yr)
{
 int y, d;
 y = yr;
 d = 4 + y + (y + 3) / 4;
 @
return (d % 7);@
if (y > 1752)
  d += 3;
 return (d % 7);
}