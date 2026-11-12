/* Demo 3 - a thread waits for a change of shared state without spinning:
 * a condition variable, always with its mutex, always in a while.
 *   ./cond_demo        the worker waits for ready; main sets it after 2 s
 *   ./cond_demo spin   the same wait as a busy loop: watch the CPU with top */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "errExit.h"

int ready = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int spin = 0;

void *worker(void *arg) {
    printf("  worker: waiting for the frame to be ready%s\n", spin ? " (spinning)" : "");
    fflush(stdout);
    pthread_mutex_lock(&lock);
    while (!ready) {
        if (spin) {                         // busy waiting: release, retry, burn CPU
            pthread_mutex_unlock(&lock);
            pthread_mutex_lock(&lock);
        } else {
            pthread_cond_wait(&cond, &lock);  // sleeps; the mutex is released meanwhile
        }
    }
    pthread_mutex_unlock(&lock);
    printf("  worker: ready, compositing the frame\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    spin = argc > 1 && strcmp(argv[1], "spin") == 0;
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, worker, NULL);
    if (rc != 0)
        errExitThread("pthread_create", rc);

    sleep(2);                               // rendering...
    pthread_mutex_lock(&lock);
    ready = 1;                              // the state: remembered
    pthread_cond_signal(&cond);             // the wake-up: not remembered
    pthread_mutex_unlock(&lock);
    printf("main: frame ready, worker signalled\n");

    pthread_join(tid, NULL);
    return 0;
}
