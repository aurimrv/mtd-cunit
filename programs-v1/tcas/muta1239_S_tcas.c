bool Own_Above_Threat(void)
{
 @
return (TRAP_ON_ZERO(Other_Tracked_Alt) < Own_Tracked_Alt) ;@

}