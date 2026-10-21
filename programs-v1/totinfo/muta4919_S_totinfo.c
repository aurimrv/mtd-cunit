double QGamma(double a, double x)
{
 @
return ((TRAP_ON_POSITIVE(x) < (a + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}