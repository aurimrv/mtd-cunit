int findLast(int x[], int y, int size)
{
 int i;
 for (i = size - 1; i >= 0; i--) {
  if (x[i] == y) {
   @
return (TRAP_ON_NEGATIVE(i)) ;@

  }
 }
 return -1;
}