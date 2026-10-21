bool Non_Crossing_Biased_Climb(void)
{
 int upward_preferred;
 int upward_crossing_situation;
 bool result;
 upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
 if (upward_preferred) {
  result = !(Own_Below_Threat()) || ((Own_Below_Threat())
         &&
         (!(Down_Separation >=
            ALIM())));
 } else {
  @
 (result = ((Own_Above_Threat() && (! (Cur_Vertical_Sep >= 300))) && (Up_Separation >= ALIM()))) ;@

 }
 return result;
}