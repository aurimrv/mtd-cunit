int patsize(char *pat, int n)
{
    int size;
    if (!in_pat_set(pat[n])) {
 (void)fprintf(stdout, "in patsize: can't happen\n");
 abort();
    } else
 switch (pat[n])
 {
 case 'c': size = 2; break;
 case '%': case '$': case '?':
     size = 1;
     break;
 case '[': case '!':
     size = pat[n + 1] + 2;
     break ;
 @
goto __LABEL_MUTA__; @
case '*':@
 UTRAP_ON_CASE(); @
@
__LABEL_MUTA__: ; @

     size = 1;
     break ;
 default:
     Caseerror(pat[n]);
 }
    return size;
}