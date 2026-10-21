double QGamma(double a, double x)
{
 @
return ((x < (a + 1.0)) ? (1.0 - gser((-10E-10) , x)) : gcf(a , x)) ;@

}