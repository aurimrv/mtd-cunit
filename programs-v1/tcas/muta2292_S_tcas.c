int alt_sep_test(void)
{
 bool enabled, tcas_equipped, intent_not_known;
 bool need_upward_RA, need_downward_RA;
 int alt_sep;
 enabled = High_Confidence && (Own_Tracked_Alt_Rate <= 600)
     && (Cur_Vertical_Sep > 600);
 tcas_equipped = Other_Capability == 1;
 intent_not_known = Two_of_Three_Reports_Valid && Other_RAC == 0;
 alt_sep = 0;
 if (enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)) {
  @
 (need_downward_RA = (Non_Crossing_Biased_Climb() && Own_Below_Threat())) ; @

  need_downward_RA = Non_Crossing_Biased_Descend()
      && Own_Above_Threat();
  if (need_upward_RA && need_downward_RA)
   alt_sep = 0;
  else if (need_upward_RA)
   alt_sep = 1;
  else if (need_downward_RA)
   alt_sep = 2;
  else
   alt_sep = 0;
 }
 return alt_sep;
}