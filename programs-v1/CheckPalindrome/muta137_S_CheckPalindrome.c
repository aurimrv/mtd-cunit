int isPalindrome(char s[])
{
 int low = 0;
 int high = strlen(s) - 1;
 while (low < high) {
  if @
( (s[low] != TRAP_ON_POSITIVE(s[high])) )@

   return 0;
  low++;
  high--;
 }
 return 1;
}