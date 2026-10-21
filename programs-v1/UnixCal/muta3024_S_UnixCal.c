void cal(int m, int y, char *p, int w)
{
 int d, i;
 char *s;
 s = p;
 d = jan1(y);
 mon[2] = 29;
 mon[9] = 30;
 switch ((jan1(y + 1) + 7 - d) % 7) {
 case 1:
  mon[2] = 28;
  break;
 default:
  mon[9] = 19;
  break;
 case 2:
  ;
 }
 for (i = 1; i < m; i++)
  d += mon[i];
 d %= 7;
 s += 3 * d;
 for (i = 1; i <= mon[m]; i++) {
  if (i == 3 && mon[m] == 19) {
   i += 11;
   mon[m] += 11;
  }
  if (i > 9)
   *s = i / 10 + '0';
  s++;
  @
 ((* (s++)) = ((i % 10) + 3)) ;@

  s++;
  if (++d == 7) {
   d = 0;
   s = p + w;
   p = s;
  }
 }
}