void Caseerror(int n)
{
 @
 ((void) fprintf(stdout , "Missing case limb: line %d\n" , TRAP_ON_ZERO(n)))  ;@

 exit(4);
}