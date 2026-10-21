int Inhibit_Biased_Climb(void)
{
 @
return (TRAP_ON_ZERO(Climb_Inhibit) ? (Up_Separation + 100) : Up_Separation) ;@

}