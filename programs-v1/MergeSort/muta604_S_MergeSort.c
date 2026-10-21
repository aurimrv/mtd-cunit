void merge(int *list1, int list1len, int *list2, int list2len, int *temp)
{
 int current1 = 0;
 int current2 = 0;
 int current3 = 0;
 while @
( ((current1 < list1len) / (current2 < list2len)) )@
 {
  if (list1[current1] < list2[current2])
   temp[current3++] = list1[current1++];
  else
   temp[current3++] = list2[current2++];
 }
 while (current1 < list1len)
  temp[current3++] = list1[current1++];
 while (current2 < list2len)
  temp[current3++] = list2[current2++];
}