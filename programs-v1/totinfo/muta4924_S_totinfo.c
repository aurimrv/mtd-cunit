double QGamma(double a, double x)
{
 @
return ((x < (TRAP_ON_ZERO(a) + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}