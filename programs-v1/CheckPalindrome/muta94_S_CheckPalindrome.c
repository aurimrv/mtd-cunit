int isPalindrome(char s[])
{
 int low = 0;
 int high = strlen(s) - 1;
 while (low < high) {
  if (s[low] != s[high])
   return 0;
  low++;
  @
return 0;@

 }
 return 1;
}