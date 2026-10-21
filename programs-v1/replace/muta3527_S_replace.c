bool in_pat_set(char c)
{
  @
return (((((((c == 'c') || (__MINCHAR__ == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}