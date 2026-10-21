int next_state(int state, char ch)
{
    if(state < 0)
      return(state);
    if(base[state]+ch >= 0)
    {@
UTRAP_ON_STAT();@
 }
    else
        return(next_state(default1[state],ch));
}