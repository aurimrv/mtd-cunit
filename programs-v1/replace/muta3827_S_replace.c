bool in_pat_set(char c)
{
  @
return (((((((c == 'c') || (TRAP_ON_NEGATIVE(c) == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}