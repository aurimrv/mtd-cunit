int isPalindrome(char s[])
{
 int low = 0;
 int high = strlen(s) - 1;
 while (low < high) {
  if @
( (s[low] != '\0') )@

   return 0;
  low++;
  high--;
 }
 return 1;
}