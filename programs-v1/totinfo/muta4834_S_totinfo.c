double QGamma(double a, double x)
{
 @
return (((-1.0) < (a + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}