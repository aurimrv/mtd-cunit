int isSorted(char *a[], int length)
{
 int i;
 for (i = 1; @
 ((-1) < length) ;@
 i++)
  if (less02(a[i], a[i - 1]))
   return 0;
 return 1;
}