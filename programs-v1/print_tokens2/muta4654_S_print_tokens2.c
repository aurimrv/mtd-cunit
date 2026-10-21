int is_spec_symbol(token str)
{
    @
return(0);@
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
    {
        return(1);
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