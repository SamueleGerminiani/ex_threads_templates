#ifndef _STATS_HH
#define _STATS_HH

// The statistics of the node, shared by every thread (given): every thread
// updates them while it renders, so they need a lock
struct stats {
    long samples;       // samples computed so far (SAMPLES x SAMPLES per pixel)
    long iterations;    // iterations spent so far
    int rows;           // rows completed so far
};

#endif
