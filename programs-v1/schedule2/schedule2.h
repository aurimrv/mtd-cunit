#define MAXPRIO 3
#define MAXLOPRIO 2
#define BLOCKPRIO 0
#define CMDSIZE 20 

#define NEW_JOB 1
#define UPGRADE_PRIO 2
#define BLOCK 3 
#define UNBLOCK 4
#define QUANTUM_EXPIRE 5
#define FINISH 6
#define FLUSH 7

#define OK 0
#define TRUE 1
#define FALSE 0
#define BADNOARGS -1 
#define BADARG -2    
#define MALLOC_ERR -3
#define BADPRIO -4   
#define BADRATIO -5   
#define NO_COMMAND -6  

struct process
{
    unsigned int pid;
    int priority;
    struct process *next;
};

extern int get_command(int *command, int *prio, float *ratio);
extern void exit_here(int status);
extern int enqueue(int prio, struct process *new_process);
extern int new_job(int prio);
extern int schedule(int command, int prio, float ratio);
extern struct process *get_current(void);
extern int reschedule(int prio);
extern int put_end(int prio, struct process *process);
extern int get_process(int prio, float ratio, struct process **job);
extern void dispatch(void);
extern int upgrade_prio(int prio, float ratio);
extern int block(void);
extern int unblock(float ratio);
extern int quantum_expire(void);
extern int finish(void);
extern int flush(void);
