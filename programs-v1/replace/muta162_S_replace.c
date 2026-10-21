int addstr(char c, char *outset, int *j, int maxset)
{
    bool result;
    if (*j >= maxset)
 @
;@

    else {
 outset[*j] = c;
 *j = *j + 1;
 result = 1;
    }
    return result;
}