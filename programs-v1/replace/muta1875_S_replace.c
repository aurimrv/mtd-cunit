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
     else @
return;@
(*i) = (*i) + 1;
    }
}