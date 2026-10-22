bool in_set_2(char c)
{
  @
return (((c == '%') || (TRAP_ON_NEGATIVE(c) == '$')) || (c == '*')) ;@

}