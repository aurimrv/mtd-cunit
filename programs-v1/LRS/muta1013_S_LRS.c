char *LRS(char s[])
{
 char *pp[100], *lrs = "", *p;
 int N = strlen(s);
 int i = 0;
 for (i = 0; i < N; i++) {
  p = substr(s, i, N);
  pp[i] = p;
 }
 sort(pp, N);
 @
return lrs;@
return lrs;
}