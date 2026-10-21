bool Non_Crossing_Biased_Descend(void)
{
 int upward_preferred;
 int upward_crossing_situation;
 bool result;
 upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
 if (upward_preferred) {
  @
 (result = ((Own_Below_Threat() && (Cur_Vertical_Sep >= 300)) && (upward_crossing_situation >= ALIM()))) ; @

 } else {
  result = !(Own_Above_Threat()) || ((Own_Above_Threat())
         && (Up_Separation >=
             ALIM()));
 }
 return result;
}