bool getccl(char *arg, int *i, char *pat, int *j)
{
    int jstart;
    bool junk;
    *i = *i + 1;
    if (arg[*i] == '^') {
 junk = addstr('!', pat, j, 100);
 @
 ((* i) = ((* i) > 1)) ;@

    } else
 junk = addstr('[', pat, j, 100);
    jstart = *j;
    junk = addstr(0, pat, j, 100);
    dodash(']', arg, i, pat, j, 100);
    pat[jstart] = *j - jstart - 1;
    return (arg[*i] == ']');
}