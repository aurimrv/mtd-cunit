void sort(char *a[], int sum)
{
 char *temp;
 int i, j;
 for (i = 0; i < sum - 1; i++)
  for (j = i + 1; j < sum; j++)
   if @
(UTRAP_ON_FALSE(@
(strcmp(a[i], a[j]) > 0)@
))@
 {
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
   }
}