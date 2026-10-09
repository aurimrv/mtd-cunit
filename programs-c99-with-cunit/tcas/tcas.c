#include <stdio.h>
#include <stdlib.h>

#define OLEV       600
#define MAXALTDIFF 600
#define MINSEP     300
#define NOZCROSS   100

typedef int bool;

int Cur_Vertical_Sep;
bool High_Confidence;
bool Two_of_Three_Reports_Valid;

int Own_Tracked_Alt;
int Own_Tracked_Alt_Rate;
int Other_Tracked_Alt;

int Alt_Layer_Value;
int Positive_RA_Alt_Thresh[4];

int Up_Separation;
int Down_Separation;

int Other_RAC;
#define NO_INTENT 0
#define DO_NOT_CLIMB 1
#define DO_NOT_DESCEND 2

int Other_Capability;
#define TCAS_TA 1
#define OTHER 2

int Climb_Inhibit;

#define UNRESOLVED 0
#define UPWARD_RA 1
#define DOWNWARD_RA 2

void initialize(void)
{
	Positive_RA_Alt_Thresh[0] = 400;
	Positive_RA_Alt_Thresh[1] = 500;
	Positive_RA_Alt_Thresh[2] = 640;
	Positive_RA_Alt_Thresh[3] = 740;
}

int ALIM(void)
{
	return Positive_RA_Alt_Thresh[Alt_Layer_Value];
}

int Inhibit_Biased_Climb(void)
{
	return (Climb_Inhibit ? Up_Separation + NOZCROSS : Up_Separation);
}

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
		result = Own_Above_Threat() && (Cur_Vertical_Sep >= MINSEP)
		    && (Up_Separation >= ALIM());
	}
	return result;
}

bool Non_Crossing_Biased_Descend(void)
{
	int upward_preferred;
	int upward_crossing_situation;
	bool result;

	upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
	if (upward_preferred) {
		result = Own_Below_Threat() && (Cur_Vertical_Sep >= MINSEP)
		    && (Down_Separation >= ALIM());
	} else {
		result = !(Own_Above_Threat()) || ((Own_Above_Threat())
						   && (Up_Separation >=
						       ALIM()));
	}
	return result;
}

bool Own_Below_Threat(void)
{
	return (Own_Tracked_Alt < Other_Tracked_Alt);
}

bool Own_Above_Threat(void)
{
	return (Other_Tracked_Alt < Own_Tracked_Alt);
}

int alt_sep_test(void)
{
	bool enabled, tcas_equipped, intent_not_known;
	bool need_upward_RA, need_downward_RA;
	int alt_sep;

	enabled = High_Confidence && (Own_Tracked_Alt_Rate <= OLEV)
	    && (Cur_Vertical_Sep > MAXALTDIFF);
	tcas_equipped = Other_Capability == TCAS_TA;
	intent_not_known = Two_of_Three_Reports_Valid && Other_RAC == NO_INTENT;

	alt_sep = UNRESOLVED;

	if (enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)) {
		need_upward_RA = Non_Crossing_Biased_Climb()
		    && Own_Below_Threat();
		need_downward_RA = Non_Crossing_Biased_Descend()
		    && Own_Above_Threat();
		if (need_upward_RA && need_downward_RA)
			alt_sep = UNRESOLVED;
		else if (need_upward_RA)
			alt_sep = UPWARD_RA;
		else if (need_downward_RA)
			alt_sep = DOWNWARD_RA;
		else
			alt_sep = UNRESOLVED;
	}

	return alt_sep;
}

