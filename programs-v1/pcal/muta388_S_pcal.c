int isleapyear(int year)
{
 @
return (((! (year % 4)) && (TRAP_ON_POSITIVE(year) % 100)) ? 1 : 0) ;@

}