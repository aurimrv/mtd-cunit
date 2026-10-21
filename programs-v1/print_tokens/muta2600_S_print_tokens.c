int keyword(int state)
{
      switch(state)
      {
          case 6 : return(6);
          case 9 : return(9);
          case 11: return(11);
          case 13: @
UTRAP_ON_STAT();@

          case 16: return(16);
          default: fprintf(stdout, "error\n");break;
      }
      exit(0);
}