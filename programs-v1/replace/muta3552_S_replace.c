bool in_pat_set(char c)
{
  @
return (((((((c == 'c') || (c == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (__MINCHAR__ == '*')) ;@

}