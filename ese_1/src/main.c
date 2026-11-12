#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "bands.h"
#include "errExit.h"
#include "mandel.h"
#include "report.h"

// The frame, shared by every thread of the process: each thread writes its
// own rows, nobody else touches them
char frame[HEIGHT][WIDTH + 1];

// The routine of a thread: renders the rows of its band with renderRow and
// adds up the iterations in the band. It receives a struct band through the
// void pointer and returns NULL
void *renderBand(void *arg) {
    struct band *b = NULL;



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

    // One band per thread: the HEIGHT rows split as evenly as possible (given)
    struct band bands[MAX_THREADS];
    for (int i = 0; i < threads; i++) {
        bands[i].first = HEIGHT * i / threads;
        bands[i].last = HEIGHT * (i + 1) / threads;
        bands[i].iterations = 0;
    }

    // Create one thread per band using 'pthread_create' with default
    // attributes (NULL), the routine renderBand and the address of the band
    // as argument. A pthread function returns 0 on success and an error
    // number on failure: use 'errExitThread' with it
    pthread_t tid[MAX_THREADS];
    for (int i = 0; i < threads; i++) {
        int rc = -1;


    }

    // Wait for every thread using 'pthread_join' (the result is not needed:
    // NULL), then add up the iterations reported in the bands
    long total = 0;
    for (int i = 0; i < threads; i++) {
        int rc = -1;



    }

    // Print the frame (given)
    for (int y = 0; y < HEIGHT; y++)
        printf("%s\n", frame[y]);
    printf("node: %d thread(s), %ld iterations\n", threads, total);

    // Render report (given): reveals code #1 when the frame is right
    report_check(frame, bands, threads);

    return 0;
}
