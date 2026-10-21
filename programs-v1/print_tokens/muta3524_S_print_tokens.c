BOOLEAN is_eof_token(token t)
{
    if@
( ((t->token_id) == 1) )@

        return(1);
    return(0);
}