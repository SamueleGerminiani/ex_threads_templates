#ifndef _QUEUE_HH
#define _QUEUE_HH

#include <pthread.h>

// The job queue of the pool (given): a bounded circular buffer of row
// numbers, shared by the main thread (producer) and the workers (consumers)
#define QUEUE_SIZE 8

struct queue {
    int rows[QUEUE_SIZE];
    int head, tail, count;      // next to take, next to put, jobs in the queue
    int closed;                 // 1 when no more jobs will be put
    pthread_mutex_t lock;       // protects every field
    pthread_cond_t notEmpty;    // signalled when a job is put
    pthread_cond_t notFull;     // signalled when a job is taken
};

// Initialize the queue (given)
void queueInit(struct queue *q);

// Put row y in the queue: waits while the queue is full
void queuePut(struct queue *q, int y);

// Take the next row from the queue: waits while the queue is empty and not
// closed. Returns the row, or -1 when the queue is empty and closed
int queueTake(struct queue *q);

// Close the queue: the workers waiting on an empty queue return -1
void queueClose(struct queue *q);

#endif
