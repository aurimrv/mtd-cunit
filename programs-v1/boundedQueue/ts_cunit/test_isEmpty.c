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

static void run_isEmpty_test(void)
{
    cunit_csv_load("test_cases_isEmpty.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *q_token = cunit_csv_cell_by_name(active_row, "q");
        char q_buf[256];
        strncpy(q_buf, q_token, sizeof(q_buf) - 1);
        q_buf[sizeof(q_buf) - 1] = '\0';
        
        int capacity = 0;
        char *init_str = NULL;
        
        char *part = strtok(q_buf, "|");
        while (part != NULL) {
            if (strncmp(part, "cap=", 4) == 0) {
                capacity = atoi(part + 4);
            } else if (strncmp(part, "init=", 5) == 0) {
                init_str = part + 5;
            }
            part = strtok(NULL, "|");
        }
        
        BoundedQueue *q = createQueue(capacity);
        
        if (init_str != NULL && strlen(init_str) > 0) {
            char *tok = strtok(init_str, ",");
            while (tok != NULL) {
                int val = atoi(tok);
                enqueue(q, val);
                tok = strtok(NULL, ",");
            }
        }
        
        int r = isEmpty(q);
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", r);
        cunit_oracle_check_output(buf);
        
        free(q->elements);
        free(q);
    }
    /* LLM_BODY_END */
}

void register_isEmpty(void)
{
    CU_add_test(cunit_suite, "isEmpty", run_isEmpty_test);
}
