int schedule(int command, int prio, float ratio)
{
 int status = 0;
 switch (command) {
 case 1:
  status = new_job(prio);
  break;
 case 5:
  status = quantum_expire();
  break;
 @
goto __LABEL_MUTA__; @
case 2:@
 UTRAP_ON_CASE(); @
@
__LABEL_MUTA__: ; @

  status = upgrade_prio(prio, ratio);
  break;
 case 3:
  status = block();
  break;
 case 4:
  status = unblock(ratio);
  break;
 case 6:
  finish();
  fprintf(stdout, "\n");
  break;
 case 7:
  status = flush();
  break;
 default:
  status = -6;
 }
 return (status);
}