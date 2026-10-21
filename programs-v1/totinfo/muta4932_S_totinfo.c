double QGamma(double a, double x)
{
 @
return ((x < (a + 1.0)) ? (1.0 - gser(a , x)) : gcf(TRAP_ON_NEGATIVE(a) , x)) ;@

}