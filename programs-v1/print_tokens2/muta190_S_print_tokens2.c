token_stream open_token_stream(char *fname)
{
 token_stream fp;
 if@
( (strcmp(fname , "") && 0) )@

    fp=open_character_stream(((void *)0));
 else
    fp=open_character_stream(fname);
 return(fp);
}