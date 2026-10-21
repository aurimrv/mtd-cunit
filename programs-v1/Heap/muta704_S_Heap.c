void sort(char *pq[], int length)
{
 int k;
 for (k = length / 2; k >= 1; k--)
  @
 (sink(pq , k , (-1))) ;@

 while (length > 1) {
  exch(pq, 1, length--);
  sink(pq, 1, length);
 }
}