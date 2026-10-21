void arraycopy(int *src, int srcstart, int *dest, int deststart, int length)
{
 int i = 0;
 while @
( (length) )@
 {
  dest[deststart + i] = src[srcstart + i];
  i++;
 }
}