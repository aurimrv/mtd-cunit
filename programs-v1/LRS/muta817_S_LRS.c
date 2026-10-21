char *LRS(char s[])
{
 char *pp[100], *lrs = "", *p;
 int N = strlen(s);
 int i = 0;
 for (i = 0; i < N; i++) {
  p = substr(s, i, N);
  pp[i] = p;
 }
 @
 (sort(pp , 0)) ;@

 for (i = 0; i < N - 1; i++) {
  char *str;
  str = lcp(pp[i], pp[i + 1]);
  if (strlen(str) > strlen(lrs)) {
   lrs = str;
  }
 }
 return lrs;
}