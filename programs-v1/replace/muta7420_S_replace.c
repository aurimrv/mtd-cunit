bool locate(character c, char *pat, int offset)
{
    int i;
    bool flag;
    flag = 0;
    i = offset + pat[offset];
    while ((i > offset))
    {
 if (c == pat[i]) {
     flag = 1;
     @
 (i = __MAXINT__) ;@

 } else
     i = i - 1;
    }
    return flag;
}