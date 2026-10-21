double QChiSq(double chisq, int df)
{
 @
return (QGamma((((double) chisq)  / 2.0) , (chisq / 2.0))) ; @

}