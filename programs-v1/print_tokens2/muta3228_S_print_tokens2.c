void print_token(token tok)
{ int type;
  type=token_type(tok);
 if(type==0)
   { fprintf(stdout, "error,\"%s\".\n",tok);
   }
 if@
( (TRAP_ON_ZERO(type) == 1) )@

   {fprintf(stdout, "keyword,\"%s\".\n",tok);
   }
 if(type==2)print_spec_symbol(tok);
 if(type==3)
   {fprintf(stdout, "identifier,\"%s\".\n",tok);
   }
 if(type==41)
   {fprintf(stdout, "numeric,%s.\n",tok);
   }
 if(type==42)
   {fprintf(stdout, "string,%s.\n",tok);
   }
 if(type==43)
   {tok=tok+1;
    fprintf(stdout, "character,\"%s\".\n",tok);
   }
 if(type==6)
   fprintf(stdout, "eof.\n");
   }