void sort(char *pq[], int length)
{
 int k;
 @
UTRAP_ON_STAT();@
while (length > 1) {
  exch(pq, 1, length--);
  sink(pq, 1, length);
 }
}