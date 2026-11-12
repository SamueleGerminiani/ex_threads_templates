#include "queue.h"

#include <stdlib.h>

#include "errExit.h"

void queueInit(struct queue *q) {
    q->head = q->tail = q->count = 0;
    q->closed = 0;
    int rc;
    if ((rc = pthread_mutex_init(&q->lock, NULL)) != 0)
        errExitThread("pthread_mutex_init", rc);
    if ((rc = pthread_cond_init(&q->notEmpty, NULL)) != 0 || (rc = pthread_cond_init(&q->notFull, NULL)) != 0)
        errExitThread("pthread_cond_init", rc);
}

void queuePut(struct queue *q, int y) {
    // Lock the queue; while it is full (count == QUEUE_SIZE) wait on
    // notFull; put y at tail, advance tail (circularly) and count; signal
    // notEmpty (a worker may be waiting for a job); unlock



    q->rows[q->tail] = y;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;


}

int queueTake(struct queue *q) {
    // Lock the queue; while it is empty and not closed wait on notEmpty;
    // if it is empty (and so closed): unlock and return -1; otherwise take
    // the row at head, advance head (circularly), decrease count, signal
    // notFull (the producer may be waiting for room); unlock; return the row







    int y = q->rows[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;


    return y;
}

void queueClose(struct queue *q) {
    // Lock the queue, set closed, wake up every worker waiting on notEmpty
    // with 'pthread_cond_broadcast' (they must all see the end), unlock

    q->closed = 1;


}
