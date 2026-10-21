int findVal(int numbers[], int length, int val)
{
 int findVal = -1;
 int i;
 for (i = 0; i < length; i++)
  if @
( (TRAP_ON_NEGATIVE(numbers[i]) == val) )@

   findVal = i;
 return findVal;
}