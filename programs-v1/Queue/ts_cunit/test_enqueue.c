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

static void run_enqueue_test(void)
{
    cunit_csv_load("test_cases_enqueue.csv");
    /* LLM_BODY_BEGIN */
    const char *pq_token;
    char pbuf[64];
    QUEUE q;
    QUEUE *pq;
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        pq_token = cunit_csv_cell_by_name(active_row, "pq");
        strncpy(pbuf, cunit_csv_cell_by_name(active_row, "p"), sizeof(pbuf) - 1);
        pbuf[sizeof(pbuf) - 1] = '\0';
        pq = &q;
        if (strcmp(pq_token, "NULL") == 0) {
            pq = NULL;
        } else if (strcmp(pq_token, "full") == 0) {
            init(&q);
            q.tail = QSIZE;
            q.head = 0;
        } else if (strcmp(pq_token, "empty") == 0) {
            init(&q);
        } else {
            init(&q);
        }
        cunit_capture_stdout_begin();
        enqueue(pq, pbuf);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
        cunit_oracle_check_output("");
    }
    /* LLM_BODY_END */
}

void register_enqueue(void)
{
    CU_add_test(cunit_suite, "enqueue", run_enqueue_test);
}
