#ifndef _MANDEL_HH
#define _MANDEL_HH

// The frame rendered by the node (given): an ASCII image of the Mandelbrot
// set, WIDTH columns by HEIGHT rows. Each pixel is sampled SAMPLES x SAMPLES
// times (antialiasing) and every sample iterates up to MAX_ITER times: a
// frame takes a few seconds of CPU on one core.
#define WIDTH 96
#define HEIGHT 40
#define MAX_ITER 20000
#define SAMPLES 4

// renderRow renders row y (0 .. HEIGHT - 1) into out, WIDTH characters
// plus the terminator, and returns the iterations it took
long renderRow(int y, char *out);

// If sampleHook is not NULL, renderRow calls it after every sample with the
// iterations of that sample (exercise 2)
extern void (*sampleHook)(long iterations);

#endif
