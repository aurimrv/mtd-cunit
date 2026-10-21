int incrdate(int argc, char **argv)
{
 static char *unit[] = {
  "sec", "min", "hour", "day", "week", "mon", "year", ""
 };
 static int conv[] = {
  1, 60, 3600, 86400, 604800, 0, 0
 };
 int i;
 double value;
 long total;
 double monthincr = 0.0, yearincr = 0.0;
 tloc = atol(argv[1]);
 argc--;
 argv++;
 argc--;
 argv++;
 value = 0.0;
 total = 0;
 while (argc &&
        ((**argv == '.') ||
  (**argv == '-') ||
  (**argv == '+') || (**argv >= '0' && **argv <= '9'))) {
  value = atof(argv[0]);
  argv++;
  argc--;
  if (argc == 0)
   missing();
  else {@
return 0;@
}
  total += (long)value;
 }
 tloc += total;
 ts = localtime(&tloc);
 ts->tm_mon += (int)monthincr;
 ts->tm_year += (int)yearincr;
 return 0;
}