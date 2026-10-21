int patsize(char *pat, int n)
{
    int size;
    if (!in_pat_set(pat[n])) {
 (void)fprintf(stdout, "in patsize: can't happen\n");
 abort();
    } else
 switch @
( (pat[2]) )@

 {
 case 'c': size = 2; break;
 case '%': case '$': case '?':
     size = 1;
     break;
 case '[': case '!':
     size = pat[n + 1] + 2;
     break ;
 case '*':
     size = 1;
     break ;
 default:
     Caseerror(pat[n]);
 }
    return size;
}