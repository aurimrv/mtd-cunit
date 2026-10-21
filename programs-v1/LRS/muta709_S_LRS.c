char *lcp(char s[], char t[])
{
 int i = 0, n;
 @
return substr(s, 0, n);@

 for (i = 0; i < n; i++) {
  if (s[i] != t[i]) {
   return substr(s, 0, i);
  }
 }
 return substr(s, 0, n);
}