# define QSIZE 10


typedef struct
{
    int head,tail;
    char names[QSIZE][30];
} QUEUE;

void enqueue(QUEUE * , char *);
char* dequeue(QUEUE *);
void display(QUEUE *);
int is_full(QUEUE *);
int is_empty(QUEUE *);
void init(QUEUE *);
