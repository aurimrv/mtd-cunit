bool in_set_2(char c)
{
  @
return (((TRAP_ON_POSITIVE(c) == '%') || (c == '$')) || (c == '*')) ;@

}