int makesub(char *arg, int from, character delim, char *sub)
{
    int result;
    int i, j;
    bool junk;
    character escjunk;
    j = 0;
    i = from;
    while ((arg[i] != delim) && (arg[i] != '\0')) {
 if ((arg[i] == (unsigned)('&')))
     junk = addstr(-1, sub, &j, 100);
 else {
     escjunk = esc(arg, &i);
     junk = addstr(escjunk, sub, &j, 100);
 }
 i = i + 1;
    }
    if (arg[i] != delim)
 @
 (result = 100) ;@

    else {
 junk = addstr('\0', &(*sub), &j, 100);
 if ((!junk))
     result = 0;
 else
     result = i;
    }
    return result;
}