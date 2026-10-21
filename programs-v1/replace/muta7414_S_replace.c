bool locate(character c, char *pat, int offset)
{
    int i;
    bool flag;
    flag = 0;
    i = offset + pat[offset];
    while ((i > offset))
    {
 if @
( (c == ((char)(-1))) )@
 {
     flag = 1;
     i = offset;
 } else
     i = i - 1;
    }
    return flag;
}