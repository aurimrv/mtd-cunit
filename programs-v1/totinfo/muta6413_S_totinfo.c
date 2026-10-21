double InfoTbl(int r, int c, const long *f, int *pdf)
{
 int i;
 int j;
 double N;
 double info = 0;
 double *xi;
 double *xj;
 int rdf = r - 1;
 int cdf = c - 1;
 if (rdf <= 0 || cdf <= 0) {
  info = -3.0;
  goto ret3;
 }
 *pdf = rdf * cdf;
 if ((xi = (double *)malloc(r * sizeof(double))) == ((void *)0)) {
  info = -4.0;
  goto ret3;
 }
 if ((xj = (double *)malloc(c * sizeof(double))) == ((void *)0)) {
  info = -4.0;
  goto ret2;
 }
 N = 0.0;
 for (i = 0; i < r; ++i) {
  double sum = 0.0;
  for (j = 0; j < c; ++j) {
   long k = f[(i)*c+(j)];
   if (k < 0L) {
    info = -2.0;
    goto ret1;
   }
   sum += (double)k;
  }
  N += xi[i] = sum;
 }
 if (N <= 0.0) {
  info = -1.0;
  goto ret1;
 }
 for (j = 0; j < c; ++j) {
  double sum = 0.0;
  for (i = 0; i < r; ++i)
   sum += (double)f[(i)*c+(j)];
  xj[j] = sum;
 }
 info = N * log(N);
 for (i = 0; i < r; ++i) {
  double pi = xi[i];
  if (pi > 0.0)
   info -= pi * log(pi);
  for (j = 0; j < c; ++j) {
   double pij = (double)f[(i)*c+(j)];
   if (pij > 0.0)
    @
 (info += (TRAP_ON_ZERO(pij) * log(pij))) ;@

  }
 }
 for (j = 0; j < c; ++j) {
  double pj = xj[j];
  if (pj > 0.0)
   info -= pj * log(pj);
 }
 info *= 2.0;
 ret1:
 free((pointer) xj);
 ret2:
 free((pointer) xi);
 ret3:
 return info;
}