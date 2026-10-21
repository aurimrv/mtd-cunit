int is_token_end(int str_com_id, char ch)
{ char ch1[2];
 ch1[0]=ch;
 ch1[1]='\0';
 if(is_eof_token(ch1)==1)return(1);
 if(str_com_id==1)
    { if(ch=='"' | ch=='\n')
         return(1);
      else
         return(0);
    }
 if@
( (str_com_id == '"') )@

   { if(ch=='\n')
        return(1);
      else
        return(0);
   }
 if(is_spec_symbol(ch1)==1) return(1);
 if(ch ==' ' || ch=='\n' || ch==59) return(1);
 return(0);
}