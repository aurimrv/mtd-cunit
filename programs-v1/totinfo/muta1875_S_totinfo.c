double LGamma(double x)
{
 static const double cof[6] = {
  76.18009173, -86.50532033, 24.01409822,
  -1.231739516, 0.120858003e-2, -0.536382e-5
 };
 double tmp, ser;
 int j;
 if (--x < 0.0) {
  double pix = 3.14159265358979323846264338327950288419716939937511 * x;
  return log(pix / sin(pix)) - LGamma(1.0 - x);
 }
 tmp = x + 5.5;
 tmp -= (x + 0.5) * log(tmp);
 ser = 1.0;
 for (@
 (j ^= 0) ;@
 j < 6; ++j)
  ser += cof[j] / ++x;
 return -tmp + log(2.50662827465 * ser);
}