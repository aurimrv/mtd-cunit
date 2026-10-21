double QGamma(double a, double x)
{
 @
return ((x < ((-10E10) + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}