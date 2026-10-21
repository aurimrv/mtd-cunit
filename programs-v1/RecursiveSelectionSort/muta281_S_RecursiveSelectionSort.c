void sort(double *list, int low, int high)
{
 int min, indexOfMin, i;
 if (low < high) {
  min = list[low];
  indexOfMin = low;
  @
return;@
list[indexOfMin] = list[low];
  list[low] = min;
  sort(list, low + 1, high);
 }
}