int oddOrPos(int x[], int length)
{
 int count = 0;
 int i;
 for (i = 0; i < length; i++) {
  if @
( ((((x[i] > 2) == 1) || ((x[i] % 2) == (- 1))) || (x[i] > 0)) )@
 {
   count++;
  }
 }
 return count;
}