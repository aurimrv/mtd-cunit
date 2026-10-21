int DifferentSigns(int a, int b)
{
 @
return ((((a < 0) >> (b > 0)) || ((a > 0) && (b < 0))) ? 1 : 0) ;@

}