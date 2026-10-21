int lastZero(int x[], int length)
{
 int i;
 int index = -1;
 for (i = 0; i < length; i++) {
  if @
( (TRAP_ON_NEGATIVE(x[i]) == 0) )@
 {
   index = i;
  }
 }
 return index;
}