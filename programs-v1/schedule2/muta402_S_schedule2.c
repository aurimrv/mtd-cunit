int get_command(int *command, int *prio, float *ratio)
{
 int status = 0;
 char buf[20];
 if (fgets(buf, 20, mystdin)) {
  *prio = *command = -1;
  *ratio = -1.0;
  sscanf(buf, "%d", command);
  switch (*command) {
  case 1:
   sscanf(buf, "%*s%d", prio);
   break;
  case 4:
   sscanf(buf, "%*s%f", ratio);
   break;
  case 2:
   sscanf(buf, "%*s%d%f", prio, ratio);
   break;
  }
  while (buf[strlen(buf) - 1] != '\n'
         && fgets(buf, 20, mystdin)) ;
  @
;@

 } else
  return (0);
}