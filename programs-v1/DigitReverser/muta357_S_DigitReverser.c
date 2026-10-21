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
{ int _PROTEUM_LOCAL_VAR_ = 1; @
while (M != 0) @
 { FALSE_AFTER_N_INTER(2); @
{
  digit = M % 10;
  s[0] = '0' + digit;
  s++;
  M = M / 10;
 }
 @
 } @
@
 } @
s[0] = '\0';
 printf("%s\n", v);
}