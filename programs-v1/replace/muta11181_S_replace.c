void change(char *pat, char *sub)
{
    string line;
    bool result;
    result = get_line(line, 100);
    while @
( ((char)(-1)) )@
 {
 subline(line, pat, sub);
 result = get_line(line, 100);
    }
}