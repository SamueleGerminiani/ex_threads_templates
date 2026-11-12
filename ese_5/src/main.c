#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"
#include "mandel.h"
#include "report.h"

#define MAX_CHILDREN 16

// The same frame as exercise 1, rendered by child processes instead of
// threads. A child has its own copy of every variable: a frame declared
// here would be rendered in the child and lost at its exit. The frame must
// live in a shared memory segment (the shared memory lab)
typedef char frame_t[HEIGHT][WIDTH + 1];

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <children>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to an integer using 'atoi': the child processes
    int children = 0;
    if (children <= 0 || children > MAX_CHILDREN) {
        printf("The number of children must be between 1 and %d!\n", MAX_CHILDREN);
        return 1;
    }

    // Create a private segment of sizeof(frame_t) bytes using 'shmget'
    // (IPC_PRIVATE, S_IRUSR | S_IWUSR) and attach it using 'shmat' (read and
    // write): the frame (use 'errExit' if a call fails)
    int shmid = -1;


    frame_t *frame = NULL;



    // Create one child per band using 'fork': child i renders the rows
    // from HEIGHT * i / children to HEIGHT * (i + 1) / children (excluded)
    // into the frame with renderRow, then terminates with 'exit'
    for (int i = 0; i < children; i++) {
        pid_t pid = -1;
        if (1 /*change this*/) {
            // fork failed: print a message using 'errExit'

        } else if (1 /*change this*/) {
            int first = HEIGHT * i / children, last = HEIGHT * (i + 1) / children;



        }
        // Parent: keep creating children
    }

    // Wait for every child using 'wait'



    // Print the frame (given)
    for (int y = 0; y < HEIGHT; y++)
        printf("%s\n", (*frame)[y]);
    printf("node: %d process(es), frame in segment %d\n", children, shmid);

    // Render report (given): reveals code #5 when the shared frame is right
    report_check(shmid, *frame, children);

    // Detach the segment using 'shmdt' and remove it using 'shmctl' and
    // IPC_RMID (use 'errExit' if a call fails)



    return 0;
}
