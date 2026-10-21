bool in_pat_set(char c)
{
  @
return (((((((__MINCHAR__ == 'c') || (c == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}