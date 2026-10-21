void putsub(char *lin, int s1, int s2, char *sub)
{
    int i;
    int j;
    @
return;@

    while ((sub[i] != '\0')) {
 if ((sub[i] == -1))
     for (j = s1; j < s2; j++)
     {
  fputc(lin[j],stdout);
     }
 else
 {
     fputc(sub[i],stdout);
 }
 i = i + 1;
    }
}