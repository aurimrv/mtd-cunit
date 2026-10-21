double QChiSq(double chisq, int df)
{
 @
return (QGamma((((double) TRAP_ON_POSITIVE(df))  / 2.0) , (chisq / 2.0))) ;@

}