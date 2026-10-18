#include "cunit_common.h"
#include "cunit_gcov.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boundedQueue.h"
/* Project function prototypes (verified at seed time). */
extern BoundedQueue *createQueue(int maxElements);
extern void enqueue(BoundedQueue *q, int e);
extern int isFull(BoundedQueue *q);
extern int isEmpty(BoundedQueue *q);
extern int dequeue(BoundedQueue *q);
extern void printBoundedQueue(BoundedQueue *q);

static void run_createQueue_test(void)
{
    cunit_csv_load("test_cases_createQueue.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *max_str = cunit_csv_cell_by_name(active_row, "maxElements");
        int maxElements = atoi(max_str);
        
        cunit_capture_stdout_begin();
        BoundedQueue *q = createQueue(maxElements);
        cunit_capture_stdout_end();
        
        const char *res = (q == NULL) ? "NULL" : "NONNULL";
        cunit_oracle_check_output(res);
        cunit_oracle_check_stdout();
        
        if (q != NULL) {
            free(q->elements);
            free(q);
        }
    }
    /* LLM_BODY_END */
}

void register_createQueue(void)
{
    CU_add_test(cunit_suite, "createQueue", run_createQueue_test);
}
