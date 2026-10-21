void pstr(char *str, int n)
{
 int i;
 char *s;
 s = str;
 i = n;
 while (i--)
  if @
( (TRAP_ON_NEGATIVE((* (s++))) == '\0') )@

   s[-1] = ' ';
 i = n + 1;
 while (i--)
  if (*--s != ' ')
   break;
 s[1] = '\0';
 printf("%s\n", str);
}