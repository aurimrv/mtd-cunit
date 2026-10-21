int is_spec_symbol(token str)
{
    if (!strcmp(str,"("))
    {
        return(1);
    }
    if (!strcmp(str,")"))
    {
        return(1);
    }
    if (!strcmp(str,"["))
    {
        return(1);
    }
    if (!strcmp(str,"]"))
    {
        return(1);
    }
    if (!strcmp(str,"'"))
    {@
UTRAP_ON_STAT();@
 }
    if (!strcmp(str,"`"))
    {
        return(1);
    }
    if (!strcmp(str,","))
    {
        return(1);
    }
    return(0);
}