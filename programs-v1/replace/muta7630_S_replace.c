bool locate(character c, char *pat, int offset)
{
    int i;
    bool flag;
    @
 (c = 0) ; @

    i = offset + pat[offset];
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