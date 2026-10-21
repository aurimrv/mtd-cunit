token_stream open_token_stream(char *fname)
{
 token_stream fp;
 if(strcmp(fname,"")==0)
    @
return(fp);@

 else
    fp=open_character_stream(fname);
 return(fp);
}