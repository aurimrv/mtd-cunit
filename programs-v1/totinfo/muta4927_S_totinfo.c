double QGamma(double a, double x)
{
 @
return ((x < (a + 1.0)) ? (1.0 - gser(TRAP_ON_ZERO(a) , x)) : gcf(a , x)) ;@

}