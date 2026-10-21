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
   if (week[i]) {
    switch (row) {
    case 0:
     printf("%2d|    %s", week[i],
            ((weeknum == 5) && (endday < numdays) && (week[i]+7 <= numdays)) ? "_/" : "  ");
     break;
    case 1:
     @
 (printf("---  %s  " , ((((weeknum == 5) && (endday < numdays)) && ((TRAP_ON_NEGATIVE(week[i]) + 7) <= numdays)) ? "_/" : "  "))) ;@

     break;
    case 2:
     printf("   %s    ",
            ((weeknum == 5) && (endday < numdays) && (week[i]+7 <= numdays)) ? "_/" : "  ");
     break;
    case 3:
     printf(" %s",
            ((weeknum == 5) && (endday < numdays) && (week[i]+7 <= numdays)) ? "_/   ---" :
            "        ");
     break;
    case 4:
     if ((weeknum == 5) && (endday < numdays) && (week[i]+7 <= numdays))
      printf("/     |%2d",
             week[i] + 7);
     else
      printf("         ");
     break;
    }
   } else
    printf("%-9.9s", spaces);
   printf("|");
  }
  printf("\n");
 }
 printf("%-*.*s",4,4,spaces);
 printf("%-*.*s\n", 71, 71, dashes);
}