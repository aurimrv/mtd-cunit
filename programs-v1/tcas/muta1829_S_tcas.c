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
 if (enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)) {@
return alt_sep;@
}
 return alt_sep;
}