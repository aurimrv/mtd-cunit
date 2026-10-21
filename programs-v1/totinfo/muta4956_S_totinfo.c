double QGamma(double a, double x)
{
 @
return ((SUCC(x) < (a + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}