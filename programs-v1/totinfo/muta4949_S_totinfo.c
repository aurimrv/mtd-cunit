double QGamma(double a, double x)
{
 @
return ((a < (a + 1.0)) ? (1.0 - gser(a , x)) : gcf(a , x)) ; @

}