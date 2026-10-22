int patsize(char *pat, int n)
{
    int size;
    if (!in_pat_set(pat[n])) {
 (void)fprintf(stdout, "in patsize: can't happen\n");
 abort();
    } else
 @
UTRAP_ON_STAT();@

    return size;
}