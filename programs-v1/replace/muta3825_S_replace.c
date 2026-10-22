bool in_pat_set(char c)
{
  @
return (((((((TRAP_ON_ZERO(c) == 'c') || (c == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (c == '!')) || (c == '*')) ;@

}