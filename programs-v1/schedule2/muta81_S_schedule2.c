void dispatch(void)
{
 int command, prio, status;
 float ratio;
 struct process *process;
 while ((status = get_command(&command, &prio, &ratio)) > 0) {
  @
 (schedule(command , prio , 0.0)) ;@

 }
 if (status < 0)
  exit_here(status);
 exit_here(0);
}