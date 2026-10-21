void invert(int a[], int N)
{
 int i;
 for (i = 0; @
 (__MAXINT__ < N) ;@
 i++) {
  if (a[i] < 0 || a[i] >= N || exists[a[i]]) {
   printf("Input is not a permutation.\n");
   return;
  }
  exists[a[i]] = 1;
 }
 for (i = 0; i < N; i++)
  ainv[a[i]] = i;
 for (i = 0; i < N; i++)
  printf("%d ", ainv[i]);
 printf("\n");
}