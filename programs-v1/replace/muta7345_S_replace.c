bool getsub(char *arg, char *sub)
{
    int makeres;
    makeres = makesub(arg, 0, '\0', sub);
    @
return (TRAP_ON_ZERO(makeres) > 0) ;@

}