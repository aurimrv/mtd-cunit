int amatch(char *lin, int offset, char *pat, int j)
{
    int i, k;
    bool result, done;
    done = 0;
    while ((!done) && (pat[j] != '\0'))
 if ((pat[j] == '*')) {
     j = j + patsize(pat, j);
     i = offset;
     while @
( ((! done) && (TRAP_ON_NEGATIVE(lin[i]) != '\0')) )@
 {
  result = omatch(lin, &i, pat, j);
  if (!result)
      done = 1;
     }
     done = 0;
     while ((!done) && (i >= offset)) {
  k = amatch(lin, i, pat, j + patsize(pat, j));
  if ((k >= 0))
      done = 1;
  else
      i = i - 1;
     }
     offset = k;
     done = 1;
 } else {
     result = omatch(lin, &offset, pat, j);
     if ((!result)) {
  offset = -1;
  done = 1;
     } else
  j = j + patsize(pat, j);
 }
     return offset;
}