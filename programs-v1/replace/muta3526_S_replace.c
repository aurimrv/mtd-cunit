bool in_pat_set(char c)
{
  @
return (((((((c == 'c') || (__MAXCHAR__ == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}