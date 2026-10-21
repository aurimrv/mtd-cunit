double gser(double a, double x)
{
 double ap, del, sum;
 int n;
 if (x <= 0.0)
  return 0.0;
 del = sum = 1.0 / (ap = a);
 for (n = 1; n <= 100; ++n) {
  sum += del *= x / ++ap;
  if (((del) < 0 ? -(del) : (del)) < ((sum) < 0 ? -(sum) : (sum)) * 3.0e-7)
   return sum * exp(-x + a * log(x) - LGamma(a));
 }
 @
return (sum * exp((((- x) + (a * log(x))) - LGamma((-10E-10))))) ;@

}