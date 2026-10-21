void trash(int x)
{
 int m, n, o;
 m = 0;
 if (x > 0)
  m = 4;
 if (x > 5)
  @
 (n = (3 * TRAP_ON_NEGATIVE(m))) ;@

 else
  n = 4 * m;
 o = takeOut(m, n);
 printf("o is: %d\n", o);
}