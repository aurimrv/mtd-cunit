void stclose(char *pat, int *j, int lastj)
{
    int jt;
    int jp;
    bool junk;
    for (jp = *j - 1; jp >= lastj ; jp--)
    {
 @
 (jt = (jp > 1)) ;@

 junk = addstr(pat[jp], pat, &jt, 100);
    }
    *j = *j + 1;
    pat[lastj] = '*';
}