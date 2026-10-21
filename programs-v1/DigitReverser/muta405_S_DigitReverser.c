void digit_reverser(int N)
{
 char v[20], *s;
 int M = 0, digit;
 while (N != 0) {
  M = (10 * M) + (N % 10);
  N = N / 10;
 }
 printf("%d\n", M);
 s = v;
 @
UTRAP_ON_STAT();@
s[0] = '\0';
 printf("%s\n", v);
}