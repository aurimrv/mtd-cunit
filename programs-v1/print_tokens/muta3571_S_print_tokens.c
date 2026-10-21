BOOLEAN is_eof_token(token t)
{
    if@
( (TRAP_ON_POSITIVE((t->token_id)) == 0) )@

        return(1);
    return(0);
}