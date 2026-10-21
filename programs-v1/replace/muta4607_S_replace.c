int makepat(char *arg, int start, char delim, char *pat)
{
    int result;
    int i, j, lastj, lj;
    bool done, junk;
    bool getres;
    char escjunk;
    j = 0;
    i = start;
    lastj = 0;
    done = 0;
    while ((!done) && (arg[i] != delim) && (arg[i] != '\0')) {
 lj = j;
 if ((arg[i] == '?'))
     junk = addstr('?', pat, &j, 100);
 else if ((arg[i] == '%') && (i == start))
     junk = addstr('%', pat, &j, 100);
 else if @
( ((arg[i] == '$') && (__MINCHAR__ == delim)) )@

     junk = addstr('$', pat, &j, 100);
 else if ((arg[i] == '['))
 {
     getres = getccl(arg, &i, pat, &j);
     done = (bool)(getres == 0);
 }
 else if ((arg[i] == '*') && (i > start))
 {
     lj = lastj;
     if (in_set_2(pat[lj]))
  done = 1;
     else
  stclose(pat, &j, lastj);
 }
 else
 {
     junk = addstr('c', pat, &j, 100);
     escjunk = esc(arg, &i);
     junk = addstr(escjunk, pat, &j, 100);
 }
 lastj = lj;
 if ((!done))
     i = i + 1;
    }
    junk = addstr('\0', pat, &j, 100);
    if ((done) || (arg[i] != delim))
 result = 0;
    else
 if ((!junk))
     result = 0;
 else
     result = i;
    return result;
}