void exch(char *pq[], int i, int j)
{
 char *swap;
 @
 (swap = pq[(__MAXINT__ - 1)]) ;@

 pq[i - 1] = pq[j - 1];
 pq[j - 1] = swap;
}