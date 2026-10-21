int next_state(int state, char ch)
{
    if(state < 0)
      return(state);
    @
return(next[base[state]+ch]);@
}