int next_state(int state, char ch)
{
    if(state < 0)
      return(state);
    if(base[state]+ch >= 0)
    {
        if@
( (check[(base[state] + ch)] == ch) ) @

             return(next[base[state]+ch]);
        else
              return(next_state(default1[state],ch));
    }
    else
        return(next_state(default1[state],ch));
}