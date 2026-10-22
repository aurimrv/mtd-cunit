bool getsub(char *arg, char *sub)
{
    int makeres;
    makeres = makesub(arg, 0, '\0', sub);
    @
return (SUCC(makeres) > 0) ;@

}