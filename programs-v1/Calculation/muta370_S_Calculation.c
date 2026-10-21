int DifferentSigns(int a, int b)
{
 @
return ((((SUCC(a) < 0) && (b > 0)) || ((a > 0) && (b < 0))) ? 1 : 0) ;@

}