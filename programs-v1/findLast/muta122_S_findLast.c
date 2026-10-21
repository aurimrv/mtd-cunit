int findLast(int x[], int y, int size)
{
 int i;
 for (i = size - 1; i >= 0; i--) {
  if (x[i] == y) {@
return -1;@
}
 }
 return -1;
}