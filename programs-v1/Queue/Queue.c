#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"

void init(QUEUE *pq)
{
	if (pq == NULL) {
		printf("Invalid Queue\n");
		return;
	}
	pq->head = pq->tail = 0;
}

int is_full(QUEUE *pq)
{
	if (pq == NULL) {
		printf("Invalid Queue\n");
		return -1;
	}
	return pq->tail == QSIZE;
}

int is_empty(QUEUE *pq)
{
	if (pq == NULL) {
		printf("Invalid Queue\n");
		return -1;
	}

	if (pq->head == pq->tail) {
		init(pq);
		return 1;
	} else
		return 0;
}

void enqueue(QUEUE *pq, char *p)
{
	if (pq == NULL) {
		printf("Invalid Queue\n");
		return;
	} else if (is_full(pq)) {
		printf("Queue is full\n");
		return;
	}
	strcpy(pq->names[(pq->tail)++], p);
	printf("\n\n\t\t Element Successfully Inserted");
}

char *dequeue(QUEUE *pq)
{
	if (pq == NULL) {
		printf("Invalid Queue\n");
		return NULL;
	} else if (is_empty(pq)) {
		printf("Queue is empty\n");
		return NULL;
	}
	return pq->names[(pq->head)++];
}

void display(QUEUE *pq)
{
	int i;
	if (pq == NULL) {
		printf("Invalid Queue\n");
		return;
	}

	for (i = pq->head; i < pq->tail; i++)
		printf("\n\t\t :%s", pq->names[i]);
	printf("\n");
}
