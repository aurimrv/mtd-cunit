int addstr(char c, char *outset, int *j, int maxset)
{
    bool result;
    if (*j >= maxset)
 result = 0;
    else {
 outset[*j] = c;
 *j = *j + 1;
 @
 (result = 0) ;@

    }
    return result;
}