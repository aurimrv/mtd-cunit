token_stream open_token_stream(char *fname)
{
 token_stream fp;
 if@
( (strcmp(fname , "")) )@

    fp=open_character_stream(((void *)0));
 else
    fp=open_character_stream(fname);
 return(fp);
}