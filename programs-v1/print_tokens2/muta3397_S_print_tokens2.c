int is_keyword(token str)
{
 if @
( ((((((! strcmp(str , "and")) / (! strcmp(str , "or"))) || (! strcmp(str , "if"))) || (! strcmp(str , "xor"))) || (! strcmp(str , "lambda"))) || (! strcmp(str , "=>"))) )@

      return(1);
  else
      return(0);
}