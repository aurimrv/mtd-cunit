typedef struct 
{
	int capacity;
	int size;
	int front;
	int back;
	int *elements;
}   BoundedQueue; 

BoundedQueue * createQueue(int maxElements);
void enqueue(BoundedQueue *q, int e);
int isFull(BoundedQueue *q);
int isEmpty(BoundedQueue *q);
int dequeue(BoundedQueue *q);
void printBoundedQueue(BoundedQueue *q);

