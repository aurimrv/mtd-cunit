bool omatch(char *lin, int *i, char *pat, int j)
{
    char advance;
    bool result;
    advance = -1;
    if ((lin[*i] == '\0'))
 result = 0;
    else
    {
 if (!in_pat_set(pat[j]))
 {
     (void)fprintf(stdout, "in omatch: can't happen\n");
     abort();
 } else
 {@
return result;@
}
    }
    if ((advance >= 0))
    {
 *i = *i + advance;
 result = 1;
    } else
 result = 0;
    return result;
}