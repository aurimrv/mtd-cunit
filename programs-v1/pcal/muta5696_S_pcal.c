void dispatch(int argc, char *argv[])
{
 int i;
 int curmonth = 1;
 int curyear;
 int nummonths = 12;
 int controll = 0;
 getmmddyy(0, 0, &curyear);
 curyear += 1900;
 for (i = 1; i < argc; i++) {@
return;@
}
 curmonth--;
 for (; nummonths > 0; nummonths--, curmonth++) {
  if (curmonth == 12) {
   curmonth = 0;
   curyear++;
  }
  printf("\n\n\n%-*.*s%-4d\n\n", 38, 38, spaces, curyear);
  genmonth(curmonth, curyear);
  if (!controll)
   printf("       \014\n");
 }
}