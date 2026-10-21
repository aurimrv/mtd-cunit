double PhiInverse02(double y, double delta, double lo, double hi)
{
 double mid = lo + (hi - lo) / 2;
 if (hi - lo < delta)
  return mid;
 if (Phi201(mid) > y)
  return PhiInverse02(y, delta, lo, mid);
 else
  @
return (PhiInverse02(y , delta , TRAP_ON_NEGATIVE(mid) , hi)) ;@

}