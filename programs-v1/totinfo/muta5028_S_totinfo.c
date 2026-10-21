double QChiSq(double chisq, int df)
{
 @
return (QGamma((((double) df)  / 2.0) , (TRAP_ON_ZERO(chisq) / 2.0))) ;@

}