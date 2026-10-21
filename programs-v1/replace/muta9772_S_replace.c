int amatch(char *lin, int offset, char *pat, int j)
{
    int i, k;
    bool result, done;
    done = 0;
    while ((!done) && (pat[j] != '\0'))
 if ((pat[j] == '*')) {@
return offset;@
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