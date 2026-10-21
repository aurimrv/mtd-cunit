void arraycopy(int *src, int srcstart, int *dest, int deststart, int length)
{
 int i = 0;
 while (i < length) {
  @
 (i = src[(srcstart + i)]) ; @

  i++;
 }
}