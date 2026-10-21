void putsub(char *lin, int s1, int s2, char *sub)
{
    int i;
    int j;
    i = 0;
    while ((sub[i] != '\0')) {
 if ((sub[i] == -1))
     for (j = s1; j < s2; j++)
     {
  fputc(lin[j],stdout);
     }
 else
 {
     @
 (fputc(sub[__MININT__] , stdout)) ;@

 }
 i = i + 1;
    }
}