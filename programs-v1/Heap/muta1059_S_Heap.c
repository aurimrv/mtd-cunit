void show(char *a[], int length)
{
 int i;
 for (i = 0; @
 (TRAP_ON_ZERO(i) < length) ;@
 i++) {
  printf("%s\n", a[i]);
 }
}