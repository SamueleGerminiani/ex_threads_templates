#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "errExit.h"
#include "mandel.h"
#include "report.h"
#include "stats.h"

#define MAX_THREADS 16

char frame[HEIGHT][WIDTH + 1];

// The shared statistics and the mutex that protects them, initialized
// statically with PTHREAD_MUTEX_INITIALIZER
struct stats stats = {0, 0, 0};
pthread_mutex_t statsLock = PTHREAD_MUTEX_INITIALIZER;

struct band {
    int first, last;
};

// Called by renderRow after every sample, from every thread at once (it
// is installed as sampleHook in main, given): it counts the sample and its
// iterations in the shared statistics. The two updates are a critical
// section: lock the mutex before them with 'pthread_mutex_lock' and unlock
// it after with 'pthread_mutex_unlock' (use 'errExitThread' if a call fails)
void countSample(long iterations) {



    stats.samples++;
    stats.iterations += iterations;



}

// Renders the rows of the band; after each row it counts the row in the
// shared statistics, under the same mutex
void *renderBand(void *arg) {
    struct band *b = (struct band *)arg;
    for (int y = b->first; y < b->last; y++) {
        renderRow(y, frame[y]);




        stats.rows += 1;



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

    // One band per thread (given); renderRow will call countSample
    struct band bands[MAX_THREADS];
    for (int i = 0; i < threads; i++) {
        bands[i].first = HEIGHT * i / threads;
        bands[i].last = HEIGHT * (i + 1) / threads;
    }
    sampleHook = countSample;

    // Create one thread per band ('pthread_create', errExitThread on error)
    pthread_t tid[MAX_THREADS];
    for (int i = 0; i < threads; i++) {
        int rc = -1;


    }

    // Meanwhile the main thread is the progress monitor: every 200 ms it
    // reads stats.rows under the mutex and prints "progress: <rows>/<HEIGHT>
    // rows", until every row is done (given: it uses the same lock)
    int done = 0;
    while (done < HEIGHT) {
        usleep(200000);
        int rc = pthread_mutex_lock(&statsLock);
        if (rc != 0)
            errExitThread("pthread_mutex_lock", rc);
        done = stats.rows;
        rc = pthread_mutex_unlock(&statsLock);
        if (rc != 0)
            errExitThread("pthread_mutex_unlock", rc);
        printf("progress: %d/%d rows\n", done, HEIGHT);
        fflush(stdout);
    }

    // Wait for every thread using 'pthread_join' (errExitThread on error)
    for (int i = 0; i < threads; i++) {
        int rc = -1;


    }

    // Print the frame and the statistics (given)
    for (int y = 0; y < HEIGHT; y++)
        printf("%s\n", frame[y]);
    printf("node: %d thread(s), %ld samples (expected %d), %ld iterations, %d rows\n", threads, stats.samples,
           WIDTH * HEIGHT * SAMPLES * SAMPLES, stats.iterations, stats.rows);

    // Render report (given): reveals code #2 when the statistics are exact
    report_check(frame, &stats, threads);

    return 0;
}
