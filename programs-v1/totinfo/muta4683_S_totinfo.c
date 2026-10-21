double gcf(double a, double x)
{
 int n;
 double gold = 0.0, fac = 1.0, b1 = 1.0, b0 = 0.0, a0 = 1.0, a1 = x;
 double g = 0.0;
 for (n = 1; n <= 100; ++n) {
  double anf;
  double an = (double)n;
  double ana = an - a;
  a0 = (a1 + a0 * ana) * fac;
  b0 = (b1 + b0 * ana) * fac;
  anf = an * fac;
  b1 = x * b0 + anf * b1;
  a1 = x * a0 + anf * a1;
  if (a1 != 0.0) {
   g = b1 * (fac = 1.0 / a1);
   gold = g - gold;
   if (((gold) < 0 ? -(gold) : (gold)) < 3.0e-7 * ((g) < 0 ? -(g) : (g)))
    return exp(-x + a * log(x) - LGamma(a)) * g;
   gold = g;
  }
 }
 @
return (exp((((- x) + (g * log(x))) - LGamma(a))) * g) ; @

}