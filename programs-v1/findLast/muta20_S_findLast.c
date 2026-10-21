int findLast(int x[], int y, int size)
{
 int i;
 for (@
 (i = (__MAXINT__ - 1)) ;@
 i >= 0; i--) {
  if (x[i] == y) {
   return i;
  }
 }
 return -1;
}