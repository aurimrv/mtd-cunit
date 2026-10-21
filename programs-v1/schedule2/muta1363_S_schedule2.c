struct process *get_current(void)
{
 int prio;
 if (!current_job) {
  @
{ int _PROTEUM_LOCAL_VAR_ = 1; @
for (prio = 3; prio > 0; prio--) @
 { TRAP_AFTER_N_INTER(2); @
{
   if (get_process(prio, 0.0, &current_job) > 0)
    break;
  }
 @
 } @
@
 } @
}
 return (current_job);
}