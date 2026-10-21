bool getccl(char *arg, int *i, char *pat, int *j)
{
    int jstart;
    bool junk;
    *i = *i + 1;
    @
return (arg[*i] == ']');@
jstart = *j;
    junk = addstr(0, pat, j, 100);
    dodash(']', arg, i, pat, j, 100);
    pat[jstart] = *j - jstart - 1;
    return (arg[*i] == ']');
}