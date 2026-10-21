double QGamma(double a, double x)
{
 @
return ((x < (0.0 + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ;@

}