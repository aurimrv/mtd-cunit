#define NEW_JOB        1
#define UPGRADE_PRIO   2 
#define BLOCK          3
#define UNBLOCK        4  
#define QUANTUM_EXPIRE 5
#define FINISH         6
#define FLUSH          7

#define MAXPRIO 3

typedef struct _job {
    struct  _job *next, *prev; 
    int          val  ;         
    short        priority;     
} Ele, *Ele_Ptr;

typedef struct list		
{
  Ele *first;
  Ele *last;
  int    mem_count;		
} List;

Ele *new_ele(int new_num);
List *new_list(void);
List *append_ele(List *a_list, Ele *a_ele);
Ele *find_nth(List *f_list, int n);
List *del_ele(List *d_list, Ele *d_ele);
void free_ele(Ele *ptr);
void finish_process(void);
void finish_all_processes(void);
void schedule(void);
void upgrade_process_prio(int prio, float ratio);
void unblock_process(float ratio);
void quantum_expire(void);
void block_process(void);
Ele *new_process(int prio);
void add_process(int prio);
void init_prio_queue(int prio, int num_proc);
void initialize(void);
void dispatch(void);
