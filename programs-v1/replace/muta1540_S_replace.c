void dodash(char delim, char *src, int *i, char *dest, int *j, int maxset)
{
    int k;
    bool junk;
    char escjunk;
    while ((src[*i] != delim) && (src[*i] != '\0'))
    {
 if (src[*i - 1] == '@') {
     escjunk = esc(src, i);
     junk = addstr(escjunk, dest, j, maxset);
 } else
     if (src[*i] != '-')
  junk = addstr(src[*i], dest, j, maxset);
     else if (*j <= 1 || src[*i + 1] == '\0')
  junk = addstr('-', dest, j, maxset);
     else if ((((*__ctype_b_loc ())[(int) ((src[*i - 1]))] & (unsigned short int) _ISalnum)) && (((*__ctype_b_loc ())[(int) ((src[*i + 1]))] & (unsigned short int) _ISalnum))
  && (src[*i - 1] <= src[*i + 1]))
  {
      for (k = src[*i-1]+1; k<=src[*i+1]; k++)
      {
   junk = addstr(k, dest, j, maxset);
      }
      *i = *i + 1;
  }
     else
  junk = addstr('-', dest, j, maxset);
 @
 ((* i) *= ((* i) + 1)) ;@

    }
}