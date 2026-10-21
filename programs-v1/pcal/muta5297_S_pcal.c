void dispatch(int argc, char *argv[])
{
 int i;
 int curmonth = 1;
 int curyear;
 int nummonths = 12;
 int controll = 0;
 getmmddyy(0, 0, &curyear);
 curyear += 1900;
 for (i = 1; i < argc; i++) {
  if (argv[i][0] == '-') {
   switch (argv[i][1]) {
   case 'm':
    if (++i == argc)
     byebye("-m requires integer arguement");
    else if ((sscanf(argv[i], "%d", &curmonth) != 1)
      || (curmonth < 1) || (curmonth > 12))
     byebye("Bad arg '%s' for -m flag\n",
            argv[i]);
    break;
   case 'n':
    if (++i == argc)
     byebye("-n requires integer arguement");
    else if @
( (! ((sscanf(argv[i] , "%d" , (& nummonths)) != 1) || (nummonths < 1))) )@

     byebye("Bad arg '%s' for -n flag\n",
            argv[i]);
    break;
   case 'y':
    if (++i == argc)
     byebye("-y requires integer arguement");
    else if (sscanf(argv[i], "%d", &curyear) != 1)
     byebye("Bad arg '%s' for -y flag\n",
            argv[i]);
    break;
   case 'l':
    controll = 1;
    break;
   case 'u':
    byebye(((void *)0));
    break;
   default:
    byebye("Bad command line arguement: %s",
           argv[i]);
    break;
   }
  } else
   byebye("Bad command line arguement: %s", argv[i]);
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