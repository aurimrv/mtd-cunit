int getpat(char *arg, char *pat)
{
    int makeres;
    @
 (makeres |= makepat(arg , 0 , '\0' , pat)) ;@

    return (makeres > 0);
}