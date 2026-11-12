/* Render report code: you do not need to read or modify this file :)
 *
 * The confirmation code is encrypted: it can only be decrypted with a key
 * computed from the correct result of the exercise.
 * The revealed code is bound to the current user and machine.
 */
#include "report.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mandel.h"

#define FNV_START 2166136261u

static unsigned int mix(unsigned int h, unsigned int v) {
    for (int i = 0; i < 4; i++) {
        h ^= (v >> (8 * i)) & 0xff;
        h *= 16777619u;
    }
    return h;
}

static unsigned int next_byte(unsigned int *s) {
    *s ^= *s << 13;
    *s ^= *s >> 17;
    *s ^= *s << 5;
    return *s & 0xff;
}

/* Decrypts 'len' bytes of 'enc' into 'out' and returns its checksum */
static unsigned int decrypt(unsigned int key, const unsigned char *enc, int len, char *out) {
    unsigned int s = key ? key : 1;
    unsigned int h = FNV_START;
    for (int i = 0; i < len; i++) {
        out[i] = enc[i] ^ next_byte(&s);
        h = mix(h, (unsigned char)out[i]);
    }
    out[len] = '\0';
    return h;
}

/* Appends to 'word' a code bound to the current user and machine */
static void bind_to_user(char *out, size_t size, const char *word) {
    const char *user = getenv("USER");
    char host[256] = "";
    char id[600];

    if (user == NULL || user[0] == '\0')
        user = "unknown";
    if (gethostname(host, sizeof(host)) != 0 || host[0] == '\0')
        strcpy(host, "unknown");
    host[sizeof(host) - 1] = '\0';

    snprintf(id, sizeof(id), "%s:%s@%s", word, user, host);
    unsigned int h = FNV_START;
    for (const char *c = id; *c != '\0'; c++) {
        h ^= (unsigned char)*c;
        h *= 16777619u;
    }
    snprintf(out, size, "%s-%04X", word, h & 0xffff);
}

static void reveal(int number, unsigned int key, const unsigned char *enc, int len, unsigned int check) {
    char word[32];
    char bound[48];
    if (decrypt(key, enc, len, word) != check)
        return;
    bind_to_user(bound, sizeof(bound), word);
    printf("\n*** Render report, code #%d of 5: \"%s\" ***\n", number, bound);
    fflush(stdout);
}

/* 1 if every sampled row of the frame is the one renderRow produces */
__attribute__((unused)) static int frame_ok(const char frame[HEIGHT][WIDTH + 1]) {
    char row[WIDTH + 1];
    for (int y = 3; y < HEIGHT; y += 7) {
        renderRow(y, row);
        if (strcmp(frame[y], row) != 0)
            return 0;
    }
    return 1;
}

/* Code #4: every row was taken from the queue exactly once, by at least
 * two different workers, the queue never held more than its capacity,
 * and the frame is right */
static pthread_mutex_t logLock = PTHREAD_MUTEX_INITIALIZER;
static int taken[HEIGHT], count = 0, overflow = 0;
static pthread_t firstWorker;
static int workersSeen = 0;

void report_job(int y, int queued) {
    pthread_mutex_lock(&logLock);
    if (workersSeen == 0) {
        firstWorker = pthread_self();
        workersSeen = 1;
    } else if (workersSeen == 1 && !pthread_equal(firstWorker, pthread_self()))
        workersSeen = 2;
    if (y >= 0 && y < HEIGHT)
        taken[y]++;
    if (queued < 0 || queued > QUEUE_SIZE)
        overflow = 1;
    count++;
    pthread_mutex_unlock(&logLock);
}

void report_check(const char frame[HEIGHT][WIDTH + 1], int workers) {
    static const unsigned char enc[] = {0x15, 0x57, 0xfe, 0x49, 0x74, 0x97, 0x5a, 0xa5, 0xf5};
    int ok = frame != NULL && workers >= 2 && count == HEIGHT && !overflow && workersSeen == 2 && frame_ok(frame);
    for (int y = 0; ok && y < HEIGHT; y++)
        if (taken[y] != 1)
            ok = 0;
    unsigned int key = mix(mix(FNV_START, 0x84), ok);
    reveal(4, key, enc, sizeof(enc), 0xd1d08548u);
}
