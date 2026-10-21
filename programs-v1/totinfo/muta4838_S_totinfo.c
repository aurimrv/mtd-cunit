double QGamma(double a, double x)
{
 @
return (((-10E-10) < (a + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}