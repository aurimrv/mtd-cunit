bool in_pat_set(char c)
{
  @
return (((((((c == 'c') || (c == '%')) || (__MAXCHAR__ == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}