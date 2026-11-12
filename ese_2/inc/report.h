#ifndef _REPORT_HH
#define _REPORT_HH

#include "mandel.h"
#include "stats.h"

/* Render report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #2 when the frame is right and the shared
 * statistics are exact. Call it after joining the threads.
 * The code is bound to the current user and machine.
 */
void report_check(const char frame[HEIGHT][WIDTH + 1], const struct stats *s, int threads);

#endif
