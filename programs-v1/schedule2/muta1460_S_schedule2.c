int reschedule(int prio)
{
 if (current_job && prio > current_job->priority) {@
return (0);@
}
 get_current();
 return (0);
}