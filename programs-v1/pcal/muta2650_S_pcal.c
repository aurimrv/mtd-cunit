void genweek(int week[], int weeknum, int startday, int daysinweek, int numdays)
{
 int i;
 int row;
 int endday;
 if (weeknum > 5)
  return;
 endday = startday + daysinweek - 1;
 for (row = 0; row < 5; row++) {
  printf("%-*.*s",4,4,spaces);
  printf("|");
  for (i = 0; i < 7; i++) {
   @
return;@
printf("|");
  }
  printf("\n");
 }
 printf("%-*.*s",4,4,spaces);
 printf("%-*.*s\n", 71, 71, dashes);
}