void quicksort(int x[], int first, int last)
{
 int pivot, j, temp, i;
 if (first < last) {
  pivot = first;
  i = first;
  j = last;
  while (i < j) {@
return;@
}
  temp = x[pivot];
  x[pivot] = x[j];
  x[j] = temp;
  quicksort(x, first, j - 1);
  quicksort(x, j + 1, last);
 }
}