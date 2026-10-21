character_stream open_character_stream(char *fname)
{ character_stream fp;
  if(fname == ((void *)0))
     fp=stdin;
  else if ((fp=fopen(fname,"r"))== ((void *)0))
  {
       @
return(fp);@

       exit(0);
  }
  return(fp);
}