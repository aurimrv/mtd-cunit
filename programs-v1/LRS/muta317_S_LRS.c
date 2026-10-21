void sort(char *a[], int sum)
{
 char *temp;
 int i, j;
 for (i = 0; i < sum - 1; i++)
  for (j = i + 1; @
 (j < TRAP_ON_POSITIVE(sum)) ;@
 j++)
   if (strcmp(a[i], a[j]) > 0) {
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
   }
}