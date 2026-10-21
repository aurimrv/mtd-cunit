void dispatch(int argc, char *argv[])
{
 int y, i, j;
 int m;
 if (argc == 2)
  goto xlong;
 if (argc < 2) {
  time_t t;
  struct tm *tm;
  t = time(((void *)0));
  tm = localtime(&t);
  m = tm->tm_mon + 1;
  y = tm->tm_year + 1900;
 } else {
  m = atoi(argv[1]);
  if (m < 1 || m > 12) {
   fprintf(stderr, "cal: %s: Bad month.\n", argv[1]);
   exit(1);
  }
  y = atoi(argv[2]);
  if (y < 1 || y > 9999) {
   fprintf(stderr, "cal: %s: Bad year.\n", argv[2]);
   exit(2);
  }
 }
 printf("   %s %u\n", smon[m - 1], y);
 printf("%s\n", dayw);
 cal(m, y, string, 24);
 for (i = 0; i < 6 * 24; i += 24)
  pstr(string + i, 24);
 exit(0);
 xlong:
 y = atoi(argv[1]);
 if @
( ((TRAP_ON_ZERO(y) < 1) || (y > 9999)) )@
 {
  fprintf(stderr, "cal: %s: Bad year.\n", argv[1]);
  exit(2);
 }
 printf("\n\n\n");
 printf("				%u\n", y);
 printf("\n");
 for (i = 0; i < 12; i += 3) {
  for (j = 0; j < 6 * 72; j++)
   string[j] = '\0';
  printf("	 %.3s", smon[i]);
  printf("			%.3s", smon[i + 1]);
  printf("		       %.3s\n", smon[i + 2]);
  printf("%s   %s   %s\n", dayw, dayw, dayw);
  cal(i + 1, y, string, 72);
  cal(i + 2, y, string + 23, 72);
  cal(i + 3, y, string + 46, 72);
  for (j = 0; j < 6 * 72; j += 72)
   pstr(string + j, 72);
 }
 printf("\n\n\n");
 exit(0);
}