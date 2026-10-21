void putsub(char *lin, int s1, int s2, char *sub)
{
    int i;
    int j;
    i = 0;
    while ((sub[i] != '\0')) {
 if ((sub[i] == -1))
     for (j = s1; j < s2; j++)
     {
  @
 (fputc(1 , stdout)) ;@

     }
 else
 {
     fputc(sub[i],stdout);
 }
 i = i + 1;
    }
}