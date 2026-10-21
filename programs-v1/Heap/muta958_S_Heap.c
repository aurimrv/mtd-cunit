int isSorted(char *a[], int length)
{
 int i;
 for (i = 1; i < length; i++)
  if @
(UTRAP_ON_FALSE(@
(less02(a[i], a[i - 1]))@
))@

   return 0;
 return 1;
}