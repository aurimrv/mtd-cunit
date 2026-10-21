double PhiInverse02(double y, double delta, double lo, double hi)
{
 double mid = lo + (hi - lo) / 2;
 if (hi - lo < delta)
  return mid;
 @
return PhiInverse02(y, delta, lo, mid);@
}