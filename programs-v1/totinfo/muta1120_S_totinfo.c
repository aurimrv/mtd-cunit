int dispatch(void)
{
 char *p;
 int i;
 int j;
 double info;
 int infodf;
 double totinfo = 0.0;
 int totdf;
 totdf = 0;
 while (fgets(line, 256, mystdin) != ((void *)0)) {
  for (p = line; *p != '\0' && ((*__ctype_b_loc ())[(int) (((int)*p))] & (unsigned short int) _ISspace); ++p) ;
  if (*p == '\0')
   continue;
  if (*p == '#') {
   (void)fputs(line, stdout);
   continue;
  }
  if (sscanf(p, "%d %d\n", &r, &c) != 2) {
   (void)fputs("* invalid row/column line *\n", stdout);
   return 1;
  }
  if (r * c > 1000) {
   (void)fputs("* table too large *\n", stdout);
   return 1;
  }
  for (i = 0; i < r; ++i)
   for (j = 0; j < c; ++j)
    if (fscanf(mystdin, " %ld", &f[(i)*c+(j)]) != 1) {
     (void)fputs("* EOF in table *\n",
          stdout);
     return 1;
    }
  info = InfoTbl(r, c, f, &infodf);
  if (info >= 0.0) {
   (void)printf("2info = %5.2f\tdf = %2d\tq = %7.4f\n",
         info, infodf, QChiSq(info, infodf)
       );
   totinfo += info;
   totdf += infodf;
  } else
   (void)fputs(info < -3.5 ? "out of memory\n"
        : info < -2.5 ? "table too small\n"
        : info < -1.5 ? "negative freq\n"
        : "table all zeros\n", stdout);
 }
 if (totdf <= 0) {@
UTRAP_ON_STAT();@
 }
 (void)printf("\ntotal 2info = %5.2f\tdf = %2d\tq = %7.4f\n",
       totinfo, totdf, QChiSq(totinfo, totdf)
     );
 return 0;
}