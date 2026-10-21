void byebye(char *fmt, ...)
{
 if (fmt != ((void *)0)) {
  va_list ap;
  __builtin_va_start(ap,fmt);
  @
 (vprintf(fmt , PRED(ap))) ;@

  __builtin_va_end(ap);
 }
 printf("\n");
 printf("Usage: pcal [-l] [-m startmonth]\n");
 printf("            [-n nummonths] [-u] [-y startyear]\n");
 printf("       startmonth:day of month to start on(1=jan...12=dec)\n");
 printf("       startyear :year to start on(1989=1989, 89=0089)\n");
 printf("                  default startday=1, startmonth=1,\n");
 printf("                  startyear=current year\n");
 printf("       nummonths :#of months to print out(default is 12)\n");
 printf
     ("       -l        :suppress printing of ^L's after each month\n");
 printf("                  default is to print them\n");
 printf("       -u        :print this synopsis\n");
 exit(0);
}