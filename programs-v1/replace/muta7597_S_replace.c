bool locate(character c, char *pat, int offset)
{
    int i;
    bool flag;
    flag = 0;
    @
 (i = (TRAP_ON_NEGATIVE(offset) + pat[offset])) ;@

    while ((i > offset))
    {
 if (c == pat[i]) {
     flag = 1;
     i = offset;
 } else
     i = i - 1;
    }
    return flag;
}