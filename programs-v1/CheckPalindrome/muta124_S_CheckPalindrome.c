int isPalindrome(char s[])
{
 int low = 0;
 int high = strlen(s) - 1;
 while @
( (TRAP_ON_ZERO(low) < high) )@
 {
  if (s[low] != s[high])
   return 0;
  low++;
  high--;
 }
 return 1;
}