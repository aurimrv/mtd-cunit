#include	<stdio.h>
#include	<instrument.h>

int ponta_de_prova (long func, int node)
{
static FILE *fp=NULL;
static long lf;
static TRACE_LOG	*pr;

   if (fp == NULL) {
	fp = fopen ("./S_CheckPalindrome.LOG.TMP", "w+");
	if (fp == NULL) {
	   perror ("Error creating log file");
	   exit (1);
 	}
	pr = new_log();
   }
   if ( ! test_node_log(pr, func, node) )
   {
	ins_node_log(pr, func, node);
   	if (lf != func)
	   fprintf (fp, "\n%ld ", -(lf = func) );
   	fprintf (fp, " %d", node);
	fflush(fp);
   }   return 1;
}


