int pat(char subject[], int subjectLen, char pattern[], int patternLen)
{
 int iSub = 0;
 int rtnIndex = -1;
 int isPat = 0;
 int iPat = 0;
 while (isPat == 0 && (iSub + patternLen - 1 < subjectLen)) {
  if (subject[iSub] == pattern[0]) {
   rtnIndex = iSub;
   isPat = 1;
   for (iPat = 1; iPat < patternLen; iPat++) {
    if (subject[iSub + iPat] != pattern[iPat]) {
     rtnIndex = -1;
     isPat = 0;
     break;
    }
   }
  }
  @
 (iSub--) ;@

 }
 return rtnIndex;
}