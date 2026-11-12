#ifndef _BANDS_HH
#define _BANDS_HH

#define MAX_THREADS 16

// The work of one thread: the rows from first (included) to last (excluded),
// and what it reports back (given)
struct band {
    int first;
    int last;
    long iterations;    // filled by the thread
};

#endif
