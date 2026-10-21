int isPalindrome(char s[])
{
 int low = 0;
 int high = strlen(s) - 1;
 while (low < high) {
  if @
( (s[low] != s[TRAP_ON_ZERO(high)]) )@

   return 0;
  low++;
  high--;
 }
 return 1;
}