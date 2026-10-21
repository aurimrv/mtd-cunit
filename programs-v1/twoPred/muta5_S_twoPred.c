char twoPred(int x, int y)
{
 int z = 0;
 if (x < y)
  z = 1;
 else
  @
 (z = 10) ;@

 if (z && x + y == 10)
  return 'A';
 else
  return 'B';
}