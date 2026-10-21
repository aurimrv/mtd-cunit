char esc(char *s, int *i)
{
    char result;
    if (s[*i] != '@')
 result = s[*i];
    else
 if (s[*i + 1] == '\0')
     result = '@';
 else
 {
     *i = *i + 1;
     @
return result;@
}
    return result;
}