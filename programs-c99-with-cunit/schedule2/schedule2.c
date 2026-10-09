#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "schedule2.h"

static struct process *current_job;
static int next_pid = 0;

FILE *mystdin;

int enqueue(int prio, struct process *new_process)
{
	int status;
	if (status = put_end(prio, new_process))
		return (status);
	return (reschedule(prio));
}

struct queue {
	int length;
	struct process *head;
};

static struct queue prio_queue[MAXPRIO + 1];

void dispatch(void)
{
	int command, prio, status;
	float ratio;
	struct process *process;

	while ((status = get_command(&command, &prio, &ratio)) > 0) {
		schedule(command, prio, ratio);
	}
	if (status < 0)
		exit_here(status);
	exit_here(OK);
}

int get_command(int *command, int *prio, float *ratio)
{
	int status = OK;
	char buf[CMDSIZE];
	if (fgets(buf, CMDSIZE, mystdin)) {
		*prio = *command = -1;
		*ratio = -1.0;
		sscanf(buf, "%d", command);
		switch (*command) {
		case NEW_JOB:
			sscanf(buf, "%*s%d", prio);
			break;
		case UNBLOCK:
			sscanf(buf, "%*s%f", ratio);
			break;
		case UPGRADE_PRIO:
			sscanf(buf, "%*s%d%f", prio, ratio);
			break;
		}

		while (buf[strlen(buf) - 1] != '\n'
		       && fgets(buf, CMDSIZE, mystdin)) ;
		return (TRUE);
	} else
		return (FALSE);
}

void exit_here(int status)
{
	exit(abs(status));
}

int new_job(int prio)
{
	int pid, status = OK;
	struct process *new_process;
	pid = next_pid++;
	new_process = (struct process *)malloc(sizeof(struct process));
	if (!new_process)
		status = MALLOC_ERR;
	else {
		new_process->pid = pid;
		new_process->priority = prio;
		new_process->next = (struct process *)0;
		status = enqueue(prio, new_process);
		if (status) {
			free(new_process);
		}
	}
	if (status)
		next_pid--;
	return (status);
}

int upgrade_prio(int prio, float ratio)
{
	int status;
	struct process *job;
	if (prio < 1 || prio > MAXLOPRIO)
		return (BADPRIO);
	if ((status = get_process(prio, ratio, &job)) <= 0)
		return (status);

	job->priority = prio + 1;
	return (enqueue(prio + 1, job));
}

int block(void)
{
	struct process *job;
	job = get_current();
	if (job) {
		current_job = (struct process *)0;
		return (enqueue(BLOCKPRIO, job));
	}
	return (OK);
}

int unblock(float ratio)
{
	int status;
	struct process *job;
	if ((status = get_process(BLOCKPRIO, ratio, &job)) <= 0)
		return (status);

	return (enqueue(job->priority, job));
}

int quantum_expire(void)
{
	struct process *job;
	job = get_current();
	if (job) {
		current_job = (struct process *)0;
		return (enqueue(job->priority, job));
	}
	return (OK);
}

int finish(void)
{
	struct process *job;
	job = get_current();
	if (job) {
		current_job = (struct process *)0;
		reschedule(0);
		fprintf(stdout, " %d", job->pid);
		free(job);
		return (FALSE);
	} else
		return (TRUE);
}

int flush(void)
{
	while (!finish()) ;
	fprintf(stdout, "\n");
	return (OK);
}

struct process *get_current(void)
{
	int prio;
	if (!current_job) {
		for (prio = MAXPRIO; prio > 0; prio--) {
			if (get_process(prio, 0.0, &current_job) > 0)
				break;
		}
	}
	return (current_job);
}

int reschedule(int prio)
{
	if (current_job && prio > current_job->priority) {
		put_end(current_job->priority, current_job);
		current_job = (struct process *)0;
	}
	get_current();
	return (OK);
}

int schedule(int command, int prio, float ratio)
{
	int status = OK;
	switch (command) {
	case NEW_JOB:
		status = new_job(prio);
		break;
	case QUANTUM_EXPIRE:
		status = quantum_expire();
		break;
	case UPGRADE_PRIO:
		status = upgrade_prio(prio, ratio);
		break;
	case BLOCK:
		status = block();
		break;
	case UNBLOCK:
		status = unblock(ratio);
		break;
	case FINISH:
		finish();
		fprintf(stdout, "\n");
		break;
	case FLUSH:
		status = flush();
		break;
	default:
		status = NO_COMMAND;
	}
	return (status);
}

int put_end(int prio, struct process *process)
{
	struct process **next;
	if (prio > MAXPRIO || prio < 0)
		return (BADPRIO);

	for (next = &prio_queue[prio].head; *next; next = &(*next)->next) ;
	*next = process;
	prio_queue[prio].length++;
	return (OK);
}

int get_process(int prio, float ratio, struct process **job)
{
	int length, index;
	struct process **next;
	if (prio > MAXPRIO || prio < 0)
		return (BADPRIO);
	if (ratio < 0.0 || ratio > 1.0)
		return (BADRATIO);
	length = prio_queue[prio].length;
	index = ratio * length;
	index = index >= length ? length - 1 : index;
	for (next = &prio_queue[prio].head; index && *next; index--)
		next = &(*next)->next;
	*job = *next;
	if (*job) {
		*next = (*next)->next;
		(*job)->next = (struct process *)0;
		prio_queue[prio].length--;
		return (TRUE);
	} else
		return (FALSE);
}
