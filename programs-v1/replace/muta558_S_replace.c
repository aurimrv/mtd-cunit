char esc(char *s, int *i)
{
    char result;
    if (s[*i] != '@')
 result = s[*i];
    else
 if (s[*i + 1] == '\0')
     result = '@';
 else
 {
     *i = *i + 1;
     if (s[*i] == 'n')
  @
 (result <<= 10) ;@

     else
  if (s[*i] == 't')
      result = 9;
  else
      result = s[*i];
 }
    return result;
}