int FnTimes(int a, int b)
{
 int sum = 0;
 int iter;
 if (a < b)
  return FnTimes(b, a);
 for (iter = abss(b); iter > 0; --iter) {
  sum += a;
 }
 if @
( (b) )@

  sum = FnNegate(sum);
 return sum;
}