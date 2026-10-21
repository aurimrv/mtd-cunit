char *lcp(char s[], char t[])
{
 int i = 0, n;
 n = minn(strlen(s), strlen(t));
 for (i = 0; i < n; i++) {
  if @
( (0 != t[i]) )@
 {
   return substr(s, 0, i);
  }
 }
 return substr(s, 0, n);
}