void subline(char *lin, char *pat, char *sub)
{
 int i, lastm, m;
 @
UTRAP_ON_STAT();@

 i = 0;
 while ((lin[i] != '\0'))
 {
     m = amatch(lin, i, pat, 0);
     if ((m >= 0) && (lastm != m)) {
  putsub(lin, i, m, sub);
  lastm = m;
     }
     if ((m == -1) || (m == i)) {
  fputc(lin[i],stdout);
  i = i + 1;
     } else
  i = m;
 }
}