#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
/* Project function prototypes (verified at seed time). */
extern void init(QUEUE *pq);
extern int is_full(QUEUE *pq);
extern int is_empty(QUEUE *pq);
extern void enqueue(QUEUE *pq, char *p);
extern char *dequeue(QUEUE *pq);
extern void display(QUEUE *pq);

static void run_dequeue_test(void)
{
    cunit_csv_load("test_cases_dequeue.csv");
    /* LLM_BODY_BEGIN */
    const char *pq_token;
    QUEUE q;
    QUEUE *pq;
    char *ret;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        pq_token = cunit_csv_cell_by_name(active_row, "pq");
        pq = &q;
        if (strcmp(pq_token, "NULL") == 0) {
            pq = NULL;
        } else if (strcmp(pq_token, "empty") == 0) {
            init(&q);
        } else if (strcmp(pq_token, "nonempty") == 0) {
            init(&q);
            strcpy(q.names[0], "first");
            q.tail = 1;
            q.head = 0;
        } else {
            init(&q);
        }
        cunit_capture_stdout_begin();
        ret = dequeue(pq);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
        cunit_oracle_check_output(ret ? ret : "NULL");
    }
    /* LLM_BODY_END */
}

void register_dequeue(void)
{
    CU_add_test(cunit_suite, "dequeue", run_dequeue_test);
}
