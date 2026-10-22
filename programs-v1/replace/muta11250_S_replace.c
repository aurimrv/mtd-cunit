void Caseerror(int n)
{
 @
 ((void) fprintf(stdout , "Missing case limb: line %d\n" , TRAP_ON_POSITIVE(n)))  ;@

 exit(4);
}