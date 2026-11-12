#ifndef _REPORT_HH
#define _REPORT_HH

#include "bands.h"
#include "mandel.h"

/* Render report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #1 when the frame is right and every band was
 * rendered by its thread. Call it after joining the threads.
 * The code is bound to the current user and machine.
 */
void report_check(const char frame[HEIGHT][WIDTH + 1], const struct band *bands, int threads);

#endif
