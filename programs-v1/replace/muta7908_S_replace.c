bool omatch(char *lin, int *i, char *pat, int j)
{
    char advance;
    bool result;
    advance = -1;
    if ((lin[*i] == '\0'))
 result = 0;
    else
    {
 if @
( (! in_pat_set(__MAXCHAR__)) )@

 {
     (void)fprintf(stdout, "in omatch: can't happen\n");
     abort();
 } else
 {
      switch (pat[j])
      {
      case 'c':
   if (lin[*i] == pat[j + 1])
       advance = 1;
   break ;
      case '%':
   if (*i == 0)
       advance = 0;
   break ;
      case '?':
   if (lin[*i] != 10)
       advance = 1;
   break ;
      case '$':
   if (lin[*i] == 10)
       advance = 0;
   break ;
      case '[':
   if (locate(lin[*i], pat, j + 1))
       advance = 1;
   break ;
      case '!':
   if ((lin[*i] != 10) && (!locate(lin[*i], pat, j+1)))
       advance = 1;
   break ;
      default:
   Caseerror(pat[j]);
      };
  }
    }
    if ((advance >= 0))
    {
 *i = *i + advance;
 result = 1;
    } else
 result = 0;
    return result;
}