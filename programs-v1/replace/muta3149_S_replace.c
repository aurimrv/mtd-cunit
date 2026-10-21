void stclose(char *pat, int *j, int lastj)
{
    int jt;
    int jp;
    bool junk;
    for (jp = *j - 1; jp >= lastj ; jp--)
    {@
return;@
}
    *j = *j + 1;
    pat[lastj] = '*';
}