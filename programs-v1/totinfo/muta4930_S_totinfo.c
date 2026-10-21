double QGamma(double a, double x)
{
 @
return ((x < (a + 1.0)) ? (1.0 - gser(a , TRAP_ON_ZERO(x))) : gcf(a , x)) ;@

}