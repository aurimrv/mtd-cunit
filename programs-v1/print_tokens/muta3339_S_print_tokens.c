int next_state(int state, char ch)
{
    if(state < 0)
      return(state);
    @
return(next_state(default1[state],ch));@
}