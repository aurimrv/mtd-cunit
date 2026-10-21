int isPalindrome(char s[])
{
 int low = 0;
 int high = strlen(s) - 1;
 while (low < high) {
  if (s[low] != s[high])
   return 0;
  @
return 0;@

  high--;
 }
 return 1;
}