#include <stdio.h>
#include <malloc.h>

#include "schedule.h"

FILE *mystdin;

Ele * new_ele(int new_num)
{
	Ele *ele;

	ele = (Ele *) malloc(sizeof(Ele));
	ele->next = NULL;
	ele->prev = NULL;
	ele->val = new_num;
	return ele;
}

List *new_list(void)
{
	List *list;

	list = (List *) malloc(sizeof(List));

	list->first = NULL;
	list->last = NULL;
	list->mem_count = 0;
	return (list);
}

List *append_ele(List *a_list, Ele *a_ele)
{
	if (!a_list)
		a_list = new_list();

	a_ele->prev = a_list->last;
	if (a_list->last)
		a_list->last->next = a_ele;
	else
		a_list->first = a_ele;
	a_list->last = a_ele;
	a_ele->next = NULL;
	a_list->mem_count++;
	return (a_list);
}

Ele *find_nth(List *f_list, int n)
{
	Ele *f_ele;
	int i;

	if (!f_list)
		return NULL;
	f_ele = f_list->first;
	for (i = 1; f_ele && (i < n); i++)
		f_ele = f_ele->next;
	return f_ele;
}

List *del_ele(List *d_list, Ele *d_ele)
{
	if (!d_list || !d_ele)
		return (NULL);

	if (d_ele->next)
		d_ele->next->prev = d_ele->prev;
	else
		d_list->last = d_ele->prev;
	if (d_ele->prev)
		d_ele->prev->next = d_ele->next;
	else
		d_list->first = d_ele->next;

	d_list->mem_count--;
	return (d_list);
}

void free_ele(Ele *ptr)
{
	free(ptr);
}

int alloc_proc_num;
int num_processes;
Ele *cur_proc;
List *prio_queue[MAXPRIO + 1];
List *block_queue;

void finish_process(void)
{
	schedule();
	if (cur_proc) {
		fprintf(stdout, "%d ", cur_proc->val);
		free_ele(cur_proc);
		num_processes--;
	}
}

void finish_all_processes(void)
{
	int i;
	int total;
	total = num_processes;
	for (i = 0; i < total; i++)
		finish_process();
}

void schedule(void)
{
	int i;

	cur_proc = NULL;
	for (i = MAXPRIO; i > 0; i--) {
		if (prio_queue[i]->mem_count > 0) {
			cur_proc = prio_queue[i]->first;
			prio_queue[i] = del_ele(prio_queue[i], cur_proc);
			return;
		}
	}
}

void upgrade_process_prio(int prio, float ratio)
{
	int count;
	int n;
	Ele *proc;
	List *src_queue, *dest_queue;

	if (prio >= MAXPRIO)
		return;
	src_queue = prio_queue[prio];
	dest_queue = prio_queue[prio + 1];
	count = src_queue->mem_count;

	if (count > 0) {
		n = (int)(count * ratio + 1);
		proc = find_nth(src_queue, n);
		if (proc) {
			src_queue = del_ele(src_queue, proc);
			proc->priority = prio;
			dest_queue = append_ele(dest_queue, proc);
		}
	}
}

void unblock_process(float ratio)
{
	int count;
	int n;
	Ele *proc;
	int prio;
	if (block_queue) {
		count = block_queue->mem_count;
		n = (int)(count * ratio + 1);
		proc = find_nth(block_queue, n);
		if (proc) {
			block_queue = del_ele(block_queue, proc);
			prio = proc->priority;
			prio_queue[prio] = append_ele(prio_queue[prio], proc);
		}
	}
}

void quantum_expire(void)
{
	int prio;
	schedule();
	if (cur_proc) {
		prio = cur_proc->priority;
		prio_queue[prio] = append_ele(prio_queue[prio], cur_proc);
	}
}

void block_process(void)
{
	schedule();
	if (cur_proc) {
		block_queue = append_ele(block_queue, cur_proc);
	}
}

Ele * new_process(int prio)
{
	Ele *proc;
	proc = new_ele(alloc_proc_num++);
	proc->priority = prio;
	num_processes++;
	return proc;
}

void add_process(int prio)
{
	Ele *proc;
	proc = new_process(prio);
	prio_queue[prio] = append_ele(prio_queue[prio], proc);
}

void init_prio_queue(int prio, int num_proc)
{
	List *queue;
	Ele *proc;
	int i;

	queue = new_list();
	for (i = 0; i < num_proc; i++) {
		proc = new_process(prio);
		queue = append_ele(queue, proc);
	}
	prio_queue[prio] = queue;
}

void initialize(void)
{
	alloc_proc_num = 0;
	num_processes = 0;
}

void dispatch(void)
{
	int command;
	int prio;
	float ratio;
	int status;

	for (status = fscanf(mystdin, "%d", &command);
	     ((status != EOF) && status);
	     status = fscanf(mystdin, "%d", &command)) {
		switch (command) {
		case FINISH:
			finish_process();
			break;
		case BLOCK:
			block_process();
			break;
		case QUANTUM_EXPIRE:
			quantum_expire();
			break;
		case UNBLOCK:
			fscanf(mystdin, "%f", &ratio);
			unblock_process(ratio);
			break;
		case UPGRADE_PRIO:
			fscanf(mystdin, "%d", &prio);
			fscanf(mystdin, "%f", &ratio);
			if (prio > MAXPRIO || prio <= 0) {
				fprintf(stdout, "** invalid priority\n");
				return;
			} else
				upgrade_process_prio(prio, ratio);
			break;
		case NEW_JOB:
			fscanf(mystdin, "%d", &prio);
			if (prio > MAXPRIO || prio <= 0) {
				fprintf(stdout, "** invalid priority\n");
				return;
			} else
				add_process(prio);
			break;
		case FLUSH:
			finish_all_processes();
			break;
		}
	}
}
