char *lcp(char s[], char t[])
{
 int i = 0, n;
 n = minn(strlen(s), strlen(t));
 for (i = 0; i < n; i++) {
  if @
( (s[i] != TRAP_ON_ZERO(t[i])) )@
 {
   return substr(s, 0, i);
  }
 }
 return substr(s, 0, n);
}