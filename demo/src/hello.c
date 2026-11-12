/* Demo 1 - threads are created, run a function, and are joined.
 * Three threads receive a struct each, print, and return a value that the
 * main thread collects with pthread_join. */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "errExit.h"

struct job {
    int id;
    const char *name;
    long result;        // filled by the thread
};

void *run(void *arg) {
    struct job *j = (struct job *)arg;
    printf("  thread %d (%s): starting, pid %d, same as main\n", j->id, j->name, getpid());
    fflush(stdout);
    sleep(1 + j->id % 2);
    j->result = 1000L * j->id;
    printf("  thread %d (%s): done\n", j->id, j->name);
    fflush(stdout);
    return j;           // a void pointer: here, the job itself
}

int main(int argc, char *argv[]) {
    struct job jobs[3] = {{0, "shadows", 0}, {1, "lights", 0}, {2, "textures", 0}};
    pthread_t tid[3];

    printf("main: pid %d, creating 3 threads\n", getpid());
    for (int i = 0; i < 3; i++) {
        int rc = pthread_create(&tid[i], NULL, run, &jobs[i]);
        if (rc != 0)
            errExitThread("pthread_create", rc);   // an error number, not errno
    }

    for (int i = 0; i < 3; i++) {
        void *result;
        int rc = pthread_join(tid[i], &result);
        if (rc != 0)
            errExitThread("pthread_join", rc);
        printf("main: joined thread %d, result %ld\n", i, ((struct job *)result)->result);
    }
    return 0;
}
