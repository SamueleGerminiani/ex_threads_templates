#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "errExit.h"
#include "mandel.h"
#include "report.h"

#define MAX_THREADS 16

// The display wants the rows in order, 0 to HEIGHT - 1, as soon as each one
// is ready. The threads render rows round robin (thread i renders rows i,
// i + threads, ...): row 5 may be ready before row 4. nextRow is the row
// the display expects next: a thread may print its row only when nextRow
// is that row. The mutex protects nextRow; the condition variable lets a
// thread wait for its turn without spinning
int nextRow = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t turn = PTHREAD_COND_INITIALIZER;

struct worker {
    int id, threads;
};

void *renderRows(void *arg) {
    struct worker *w = (struct worker *)arg;
    char row[WIDTH + 1];
    for (int y = w->id; y < HEIGHT; y += w->threads) {
        renderRow(y, row);

        // Wait for the turn of row y: lock the mutex; while nextRow is not
        // y, wait on the condition variable with 'pthread_cond_wait' (it
        // releases the mutex while waiting and takes it back before
        // returning)
        int rc = -1;


        while (1 /*change this*/) {



        }

        // Our turn: print the row (given), call report_row (given)
        printf("%s\n", row);
        fflush(stdout);
        report_row(y, row);

        // Pass the turn: nextRow++, then wake up every waiting thread with
        // 'pthread_cond_broadcast' (the one whose row is next will go on,
        // the others go back to waiting), and unlock the mutex







    }
    return NULL;
}

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <threads>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to an integer using 'atoi': the threads of the node
    int threads = 0;
    if (threads <= 0 || threads > MAX_THREADS) {
        printf("The number of threads must be between 1 and %d!\n", MAX_THREADS);
        return 1;
    }

    // Create the threads ('pthread_create', errExitThread on error), each
    // one with its own struct worker (given)
    struct worker workers[MAX_THREADS];
    pthread_t tid[MAX_THREADS];
    for (int i = 0; i < threads; i++) {
        workers[i].id = i;
        workers[i].threads = threads;
        int rc = -1;


    }

    // Wait for every thread using 'pthread_join' (errExitThread on error)
    for (int i = 0; i < threads; i++) {
        int rc = -1;


    }
    printf("node: %d thread(s), %d rows displayed\n", threads, nextRow);

    // Render report (given): reveals code #3 when the rows came out in order
    report_check();

    return 0;
}
