double QGamma(double a, double x)
{
 @
return ((x < (1.0 + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}