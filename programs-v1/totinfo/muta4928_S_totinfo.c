double QGamma(double a, double x)
{
 @
return ((x < (a + 1.0)) ? (1.0 - gser(a , TRAP_ON_POSITIVE(x))) : gcf(a , x)) ;@

}