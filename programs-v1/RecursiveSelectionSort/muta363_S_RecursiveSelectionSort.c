void sort(double *list, int low, int high)
{
 int min, indexOfMin, i;
 if (low < high) {
  min = list[low];
  indexOfMin = low;
  for (i = low + 1; i <= high; i++) {
   if (list[i] < min) {
    min = list[i];
    indexOfMin = i;
   }
  }
  @
 (list[TRAP_ON_NEGATIVE(indexOfMin)] = list[low]) ;@

  list[low] = min;
  sort(list, low + 1, high);
 }
}