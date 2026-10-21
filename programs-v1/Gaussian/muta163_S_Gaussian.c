double phi(double x, double mu, double sigma)
{
 @
return (phi01(((x - TRAP_ON_POSITIVE(mu)) / sigma)) / sigma) ;@

}