bool in_pat_set(char c)
{
  @
return (((((((c == 'c') || (c == '%')) || (c == '$')) || (c == '?')) || (c == '[')) || (TRAP_ON_ZERO(c) == '!')) || (c == '*')) ;@

}