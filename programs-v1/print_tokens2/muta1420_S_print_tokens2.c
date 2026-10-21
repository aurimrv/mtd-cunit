token get_token(token_stream tp)
{
  int i=0,j;
  int id=0;
  char ch,ch1[2];
  for (j=0;j<=80;j++)
      { buffer[j]='\0';}
   ch1[0]='\0';
   ch1[1]='\0';
   ch=get_char(tp);
   while(ch==' '||ch=='\n')
      {
       ch=get_char(tp);
      }
   buffer[i]=ch;
   if(is_eof_token(buffer)==1)return(buffer);
   if(is_spec_symbol(buffer)==1)return(buffer);
   if(ch =='"')id=1;
   if(ch ==59)id=2;
   ch=get_char(tp);
   while (is_token_end(id,ch) == 0)
   {
       i++;
       buffer[i]=ch;
       ch=get_char(tp);
   }
   ch1[0]=ch;
   if(is_eof_token(ch1)==1)
      { ch=unget_char(ch,tp);
        if(ch==(-1))unget_error(tp);
        return(buffer);
      }
   if(is_spec_symbol(ch1)==1)
      { ch=unget_char(ch,tp);
        if@
(UTRAP_ON_FALSE(@
(ch==(-1))@
))@
unget_error(tp);
        return(buffer);
      }
   if(id==1)
     { i++;
       buffer[i]=ch;
       return(buffer);
     }
   if(id==0 && ch==59)
     { ch=unget_char(ch,tp);
       if(ch==(-1))unget_error(tp);
       return(buffer);
     }
  return(buffer);
}