int flush(void)
{
 while (!finish()) ;
 fprintf(stdout, "\n");
 @
;@

}