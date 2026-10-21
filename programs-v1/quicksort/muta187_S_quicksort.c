void quicksort(int x[], int first, int last)
{
 int pivot, j, temp, i;
 if (first < last) {
  pivot = first;
  i = first;
  j = last;
  while (i < j) {
   while (x[i] <= x[pivot] && i < last)
    i++;
   while (x[j] > x[pivot])
    j--;
   if (i < j) {
    temp = x[i];
    x[i] = x[j];
    x[j] = temp;
   }
  }
  temp = x[pivot];
  @
 (x[pivot] = x[__MAXINT__]) ;@

  x[j] = temp;
  quicksort(x, first, j - 1);
  quicksort(x, j + 1, last);
 }
}