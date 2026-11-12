/* Demo 2 - threads share every variable: no copy, and no protection.
 *   ./race_demo        two threads add 1 to a counter 1000000 times each:
 *                      the total is less than 2000000 (lost updates)
 *   ./race_demo lock   each increment under a mutex: exact (and slower) */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "errExit.h"

#define INCREMENTS 1000000

long counter = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int lock = 0;

void *work(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        if (lock)
            pthread_mutex_lock(&m);
        counter++;      // load, add, store: three steps, and no latch between them
        if (lock)
            pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    lock = argc > 1;
    pthread_t a, b;
    int rc;
    if ((rc = pthread_create(&a, NULL, work, NULL)) != 0 || (rc = pthread_create(&b, NULL, work, NULL)) != 0)
        errExitThread("pthread_create", rc);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    printf("two threads, %d increments each, %s: counter = %ld (expected %d)\n", INCREMENTS, lock ? "with the mutex" : "no mutex", counter, 2 * INCREMENTS);
    return 0;
}
