void print_spec_symbol(token str)
{
    if (!strcmp(str,"("))
    {
             fprintf(stdout, "%s\n","lparen.");
             return;
    }
    if (!strcmp(str,")"))
    {
             fprintf(stdout, "%s\n","rparen.");
             return;
    }
    if (!strcmp(str,"["))
    {@
UTRAP_ON_STAT();@
 }
    if (!strcmp(str,"]"))
    {
             fprintf(stdout, "%s\n","rsquare.");
             return;
    }
    if (!strcmp(str,"'"))
    {
             fprintf(stdout, "%s\n","quote.");
             return;
    }
    if (!strcmp(str,"`"))
    {
             fprintf(stdout, "%s\n","bquote.");
             return;
    }
             fprintf(stdout, "%s\n","comma.");
}