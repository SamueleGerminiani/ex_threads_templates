#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "errExit.h"
#include "mandel.h"
#include "queue.h"
#include "report.h"

#define MAX_WORKERS 16

char frame[HEIGHT][WIDTH + 1];
struct queue jobs;

// A worker: takes rows from the queue with queueTake until it returns -1,
// renders each one into the frame (and calls report_job, given, with the
// row and the jobs left in the queue), then returns the rows it rendered
// as its result, through the pointer it received (an int of the main thread)
void *worker(void *arg) {
    int *rendered = NULL;

    int y = -1;
    while (1 /*change this*/) {
        report_job(y, jobs.count);


    }
    return rendered;
}

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <workers>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to an integer using 'atoi': the workers of the pool
    int workers = 0;
    if (workers <= 0 || workers > MAX_WORKERS) {
        printf("The number of workers must be between 1 and %d!\n", MAX_WORKERS);
        return 1;
    }

    queueInit(&jobs);

    // Create the workers ('pthread_create', errExitThread on error): each
    // one receives the address of its counter in rendered[]
    pthread_t tid[MAX_WORKERS];
    int rendered[MAX_WORKERS];
    for (int i = 0; i < workers; i++) {
        int rc = -1;


    }

    // The main thread is the producer: it puts every row in the queue with
    // queuePut (it waits when the queue is full), then closes the queue




    // Wait for every worker with 'pthread_join', collecting its result (a
    // pointer to its counter) in a void pointer, and print
    // "worker <i>: <n> rows" (errExitThread on error)
    for (int i = 0; i < workers; i++) {
        void *result = NULL;
        int rc = -1;


        printf("worker %d: %d rows\n", i, *(int *)result);
    }

    // Print the frame (given)
    for (int y = 0; y < HEIGHT; y++)
        printf("%s\n", frame[y]);

    // Render report (given): reveals code #4 when the pool rendered every row once
    report_check(frame, workers);

    return 0;
}
