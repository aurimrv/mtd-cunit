bool in_pat_set(char c)
{
  @
return (((((((__MAXCHAR__ == 'c') || (c == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}