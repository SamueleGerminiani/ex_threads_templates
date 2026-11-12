/* Demo 4 - how a thread ends, and what happens to the others.
 *   ./exit_demo           main returns: the process ends, the threads with it
 *   ./exit_demo wait      main calls pthread_exit: the threads go on
 *   ./exit_demo detach    a detached thread: no join, resources freed at its end */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "errExit.h"

void *slowThread(void *arg) {
    for (int i = 1; i <= 3; i++) {
        printf("  thread: step %d\n", i);
        fflush(stdout);
        sleep(1);
    }
    printf("  thread: done\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    const char *mode = argc > 1 ? argv[1] : "return";
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, slowThread, NULL);
    if (rc != 0)
        errExitThread("pthread_create", rc);

    if (strcmp(mode, "detach") == 0) {
        pthread_detach(tid);                // it cannot be joined any more
        printf("main: thread detached, main waits 4 s then returns\n");
        sleep(4);
        return 0;
    }
    if (strcmp(mode, "wait") == 0) {
        printf("main: pthread_exit: main ends, the process goes on with the thread\n");
        pthread_exit(NULL);
    }
    printf("main: returning after 1 s: the process ends, the thread with it\n");
    sleep(1);
    return 0;                               // exit(): every thread dies here
}
