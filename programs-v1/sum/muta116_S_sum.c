int sum(int x[], int size)
{
 int s = 0;
 int i;
 for (i = 0; @
 (i < TRAP_ON_NEGATIVE(size)) ;@
 i++) {
  s = s + x[i];
 }
 return s;
}