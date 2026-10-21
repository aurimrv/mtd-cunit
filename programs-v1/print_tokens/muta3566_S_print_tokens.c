BOOLEAN is_eof_token(token t)
{
    if@
(UTRAP_ON_FALSE(@
(t->token_id==0)@
))@

        return(1);
    return(0);
}