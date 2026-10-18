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

static void run_is_full_test(void)
{
    cunit_csv_load("test_cases_is_full.csv");
    /* LLM_BODY_BEGIN */
    const char *pq_token;
    QUEUE q;
    QUEUE *pq;
    int ret;
    char buf[32];
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        pq_token = cunit_csv_cell_by_name(active_row, "pq");
        pq = &q;
        if (strcmp(pq_token, "NULL") == 0) {
            pq = NULL;
        } else if (strcmp(pq_token, "full") == 0) {
            init(&q);
            q.tail = QSIZE;
            q.head = 0;
        } else if (strcmp(pq_token, "notfull") == 0) {
            init(&q);
            q.tail = 0;
            q.head = 0;
        } else {
            init(&q);
        }
        cunit_capture_stdout_begin();
        ret = is_full(pq);
        cunit_capture_stdout_end();
        cunit_oracle_check_stdout();
        snprintf(buf, sizeof(buf), "%d", ret);
        cunit_oracle_check_output(buf);
    }
    /* LLM_BODY_END */
}

void register_is_full(void)
{
    CU_add_test(cunit_suite, "is_full", run_is_full_test);
}
