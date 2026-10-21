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
 @
UTRAP_ON_STAT();@
if (totdf <= 0) {
  (void)fputs("\n*** no information accumulated ***\n", stdout);
  return 1;
 }
 (void)printf("\ntotal 2info = %5.2f\tdf = %2d\tq = %7.4f\n",
       totinfo, totdf, QChiSq(totinfo, totdf)
     );
 return 0;
}