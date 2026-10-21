char *lcp(char s[], char t[])
{
 int i = 0, n;
 n = minn(strlen(s), strlen(t));
 for (i = 0; @
 (i < __MAXINT__) ;@
 i++) {
  if (s[i] != t[i]) {
   return substr(s, 0, i);
  }
 }
 return substr(s, 0, n);
}