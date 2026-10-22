void change(char *pat, char *sub)
{
    string line;
    bool result;
    result = get_line(line, 100);
    while @
( (TRAP_ON_ZERO(result)) )@
 {
 subline(line, pat, sub);
 result = get_line(line, 100);
    }
}