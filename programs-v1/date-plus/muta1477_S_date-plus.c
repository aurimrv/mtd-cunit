int printdate(int argc, char **argv)
{
 char *format;
 static char *month[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
 };
 static char *day[] = {
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
 };
 if @
( (argc == '\n') )@
 {
  argv[0] = "%H:%M %h %d";
  argc++;
 }
 while (argc > 0) {
  format = argv[0];
  while (*format) {
   if (*format != '%')
    putchar(*format);
   else if (format[1])
    switch (*++format) {
    case 'n':
     putchar('\n');
     break;
    case 't':
     putchar('\t');
     break;
    case 'S':
     printf("%02d", ts->tm_sec);
     break;
    case 'Z':
     printf("%ld", tloc);
     break;
    case 'M':
     printf("%02d", ts->tm_min);
     break;
    case 'H':
     printf("%02d", ts->tm_hour);
     break;
    case 'T':
     printf("%02d:%02d:%02d",
            ts->tm_hour, ts->tm_min,
            ts->tm_sec);
     break;
    case 'd':
     printf("%02d", ts->tm_mday);
     break;
    case 'm':
     printf("%02d", ts->tm_mon + 1);
     break;
    case 'h':
     printf("%s", month[ts->tm_mon]);
     break;
    case 'y':
     printf("%02d", ts->tm_year);
     break;
    case 'w':
     printf("%1d", ts->tm_wday);
     break;
    case 'a':
     printf("%s", day[ts->tm_wday]);
     break;
    case 'D':
     printf("%02d/%02d/%02d",
            ts->tm_mon + 1, ts->tm_mday,
            ts->tm_year);
     break;
    case 'j':
     printf("%d", ts->tm_yday);
     break;
    default:
     fprintf(stderr,
      "date+: Bad format character: '%c'\n",
      *format);
     exit(1);
    }
   format++;
  }
  argc--;
  argv++;
  if (argc > 0)
   putchar(' ');
 }
 putchar('\n');
 return 0;
}