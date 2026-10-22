bool in_pat_set(char c)
{
  @
return (((((((TRAP_ON_POSITIVE(c) == 'c') || (c == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}