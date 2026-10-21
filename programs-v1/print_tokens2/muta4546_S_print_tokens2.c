void print_spec_symbol(token str)
{
    @
return;@
if (!strcmp(str,")"))
    {
             fprintf(stdout, "%s\n","rparen.");
             return;
    }
    if (!strcmp(str,"["))
    {
             fprintf(stdout, "%s\n","lsquare.");
             return;
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