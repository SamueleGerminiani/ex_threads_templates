#include "errExit.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void errExit(const char *msg) {
    perror(msg);
    exit(1);
}

void errExitThread(const char *msg, int rc) {
    fprintf(stderr, "%s: %s\n", msg, strerror(rc));
    exit(1);
}
